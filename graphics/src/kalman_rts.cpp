#include "Eigen/Dense"
#include "unsupported/Eigen/MatrixFunctions"

#include <graphics/kalman_rts.h>
#include "nlopt/nlopt.h"
#define kalman_min(a,b) (a<b?a:b)

namespace graphics {

	std::vector<real> diff(const std::vector<real>& in)
	{
		if (in.size() < 2) return in;
		std::vector<real> out(in.size() - 1);
		for (int i = 0; i < out.size(); i++) {
			out[i] = in[i + 1] - in[i];
		}
		return out;
	}
	std::vector<vec4> diff(const std::vector<vec4>& in)
	{
		if (in.size() < 2) return in;
		std::vector<vec4> out(in.size() - 1);
		for (int i = 0; i < out.size(); i++) {
			out[i] = in[i + 1] - in[i];
		}
		return out;
	}
	real mean(const std::vector<real>& in)
	{
		real sum = 0;
		for (int i = 0; i < in.size(); i++)
			sum += in[i];
		return sum / real(in.size());
	}
	vec3 mean(const std::vector<vec3>& in)
	{
		vec3 sum = 0;
		for (int i = 0; i < in.size(); i++)
			sum += in[i];
		return sum / real(in.size());
	}

	std::vector<vec3> smooth(const std::vector<vec3>& in, int filter_size)
	{
		std::vector<vec3> out(in.size());
		int w = filter_size / 2;
		for (int i = 0; i < in.size(); i++) {
			vec3 sum(0);
			int cnt = 0;

			for (int j = 0;  j <= w; j++) {
				if (j == 0) {
					sum += in[i];
					cnt++;
					continue;
				}
				if ( i-j >= 0 && i+j < in.size()) {
					sum += in[i-j];
					sum += in[i+j];
					cnt+=2;
				}
			}
			out[i] = sum / real(cnt);
		}
		return out;
	}

	std::vector<vec4> linear_interp(const std::vector<real>&t, const std::vector<vec4>& g, const std::vector<real>&new_t)
	{
		std::vector<vec4> out(new_t.size(), vec4(0));
		for (int i = 0; i < new_t.size(); i++) {
			real tt = new_t[i];
			if (tt < t[0]) { // extrapolation
				out[i] = ((t[0] - tt) / (t[1] - t[0]))*(g[0] - g[1]) + g[0];
				continue;
			}
			if (tt > t[t.size() - 1]) { // extrapolation
				out[i] = ((tt - t[t.size()-1]) / (t[t.size()-1] - t[t.size()-2]))*(g[t.size() - 1] - g[t.size() - 2]) + g[t.size() - 1];
				continue;
			}
			for (int j = 0; j < t.size() - 1; j++) {
				if (tt >= t[j] && tt <= t[j + 1]) {
					tt = (tt - t[j])/(t[j+1]-t[j]);
					out[i] = g[j] * (1.0 - tt) + g[j + 1] * tt;
					break;
				}
			}
		}
		return out;
	}

	std::vector<vec4> linear_quater_interp(const std::vector<real>&t, const std::vector<vec4>& g, const std::vector<real>&new_t)
	{
		std::vector<vec4> out(new_t.size(), vec4(0));
		for (int i = 0; i < new_t.size(); i++) {
			real tt = new_t[i];
			if (tt < t[0]) { // extrapolation
				out[i] = ((t[0] - tt) / (t[1] - t[0]))*(g[0] - g[1]) + g[0];
				continue;
			}
			if (tt > t[t.size() - 1]) { // extrapolation
				out[i] = ((tt - t[t.size() - 1]) / (t[t.size() - 1] - t[t.size() - 2]))*(g[t.size() - 1] - g[t.size() - 2]) + g[t.size() - 1];
				continue;
			}
			for (int j = 0; j < t.size() - 1; j++) {
				if (tt >= t[j] && tt <= t[j + 1]) {
					tt = (tt - t[j]) / (t[j + 1] - t[j]);
					out[i] =  slerp(g[j], g[j + 1], tt);//
					break;
				}
			}
		}
		return out;
	}

	std::vector<vec3> linear_interp(const std::vector<real>&t, const std::vector<vec3>& g, const std::vector<real>&new_t)
	{
		std::vector<vec3> out(new_t.size(), vec3(0));
		for (int i = 0; i < new_t.size(); i++) {
			real tt = new_t[i];
			if (tt < t[0]) { // extrapolation
				out[i] = ((t[0] - tt) / (t[1] - t[0]))*(g[0] - g[1]) + g[0];
				continue;
			}
			if (tt > t[t.size() - 1]) { // extrapolation
				out[i] = ((tt - t[t.size() - 1]) / (t[t.size() - 1] - t[t.size() - 2]))*(g[t.size() - 1] - g[t.size() - 2]) + g[t.size() - 1];
				continue;
			}
			for (int j = 0; j < t.size() - 1; j++) {
				if (tt >= t[j] && tt <= t[j + 1]) {
					tt = (tt - t[j]) / (t[j + 1] - t[j]);
					out[i] = g[j] * (1.0 - tt) + g[j + 1] * tt;
					break;
				}
			}
		}
		return out;
	}

// return residual after registration
	real register_directions(const std::vector<vec3>& pangVis,
		const std::vector<vec3>& angImu,
		const std::vector<real>& t,
		real td,
		matrix3x3& Rs,
		vec3& bias)
	{
		std::vector<real> new_t(t.size());
		for (int i = 0; i < new_t.size(); i++) {
			new_t[i] = t[i] - td;
		}
		std::vector<vec3> angVis = linear_interp(new_t, pangVis, t);
		int N = angVis.size();
		vec3 mean_angVis = mean(angVis);
		vec3 mean_angImu = mean(angImu);

		Eigen::MatrixXd P(N, 3);
		Eigen::MatrixXd Q(N, 3);
		
		for (int i = 0; i < N; i++)
		{
			P(i, 0) = angImu[i][0]-mean_angImu[0];
			P(i, 1) = angImu[i][1] - mean_angImu[1];
			P(i, 2) = angImu[i][2] - mean_angImu[2];
			Q(i, 0) = angVis[i][0] - mean_angVis[0];
			Q(i, 1) = angVis[i][1] - mean_angVis[1];
			Q(i, 2) = angVis[i][2] - mean_angVis[2];
		}

		Eigen::MatrixXd Out = P.transpose()*Q;

		Eigen::BDCSVD<Eigen::MatrixXd> usv(Out, Eigen::ComputeFullV | Eigen::ComputeFullU);
		Eigen::Matrix3d C = Eigen::Matrix3d::Identity();
		if ((usv.matrixV()*usv.matrixU().transpose()).determinant() < 0.0) {
			C(2, 2) = -1.0;
		}
		Eigen::Matrix3d r = usv.matrixV()*C*usv.matrixU().transpose();
		Eigen::MatrixXd amg(1, 3);
		amg << mean_angImu[0], mean_angImu[1], mean_angImu[2];
		amg = amg*r;
		bias[0] = mean_angVis[0] - amg(0, 0);
		bias[1] = mean_angVis[1] - amg(0, 1);
		bias[2] = mean_angVis[2] - amg(0, 2);
		real sum = 0;
		for (int i = 0; i < angVis.size(); i++) {
			amg << angImu[i][0], angImu[i][1], angImu[i][2]; 
			amg = amg * r;
			real a = angVis[i][0] - (amg(0, 0) + bias[0]);
			sum += a * a;
			a = angVis[i][1] - (amg(0, 1) + bias[1]);
			sum += a * a;
			a = angVis[i][2] - (amg(0, 2) + bias[2]);
			sum += a * a;
		}
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				Rs(i, j) = r(i, j);
		return sum;

	}

	void alignCameraIMU(std::vector<vec3>& accVis,
		std::vector<vec4>&qtVis,
		std::vector<real>& tVis,
		std::vector<vec3>& accImu,
		std::vector<real>&  tImu,
		matrix3x3& Rs, real td)
	{
		real timeStop = kalman_min(tVis[tVis.size() - 1], tImu[tImu.size() - 1]);
		int n = 0;
		for (int i = 0; i < tVis.size(); i++) {
			if (tVis[i] <= timeStop) n++;
		}
		tVis.resize(n);
		qtVis.resize(n);
		accVis.resize(n);
		n = 0;
		for (int i = 0; i < tImu.size(); i++) {
			if (tImu[i] <= timeStop) n++;
		}
		tImu.resize(n);
		accImu.resize(n);
		std::vector<real>&t = tImu;

		for (int i = 0; i < tVis.size(); i++) {
			tVis[i] = tVis[i] - td;
		}

		accVis = linear_interp(tVis, accVis, t);
		qtVis = linear_quater_interp(tVis, qtVis, t);//linear_quater_interp(tVis, qtVis, t)
		matrix3x3 rr = Rs;
		rr.transpose();
		for (int i = 0; i < accImu.size(); i++) {
			accImu[i] = rr*accImu[i];
		}
	}


	void estimateAlignment(const std::vector<quater>&qtVis_p,
		const std::vector<real>&tVis_p,
		const std::vector<vec3>&angImu_p,
		const std::vector<real>& tImu_p,
		matrix3x3& Rs,
		real& td,
		vec3& bg)
	{
		std::vector<quater> qtVis = qtVis_p;
		std::vector<real> tVis = tVis_p;
		std::vector<vec3> angImu = angImu_p;
		std::vector<real> tImu = tImu_p;

		real timeStop = kalman_min(tVis[tVis.size() - 1], tImu[tImu.size() - 1]);
		int n = 0;
		for (int i = 0; i < tVis.size(); i++) {
			if (tVis[i] <= timeStop) n++;
		}
		tVis.resize(n);
		qtVis.resize(n);
		n = 0;
		for (int i = 0; i < tImu.size(); i++) {
			if (tImu[i] <= timeStop) n++;
		}
		tImu.resize(n);
		angImu.resize(n);

		std::vector<real> t = tImu;
		real dt = mean(diff(t));
		qtVis = linear_quater_interp(tVis, qtVis, t);
		std::vector<quater> qtDiffs = diff(qtVis);
		qtDiffs.push_back(qtDiffs[qtDiffs.size() - 1]);
		std::vector<vec3> angVis(qtDiffs.size(), vec3(0));
		for (int i = 0; i < qtDiffs.size(); i++) {
			quater q = inv(qtVis[i]);
			real sz = norm(q);
			q[1] = q[1] / sz;
			q[2] = q[2] / sz;
			q[3] = q[3] / sz;
			q = -(2.0 / dt)*(qtDiffs[i] & q);
			angVis[i] = vec3(q[1], q[2], q[3]);
		}
		angVis = smooth(angVis, 15);
		angImu = smooth(angImu, 15);

		real gRatio = (1 + sqrt(5)) / 2;
		real tolerance = 0.0001;

		real maxOffset = 0.5;
		real a = -maxOffset;
		real b = maxOffset;

		real c = b - (b - a) / gRatio;
		real d = a + (b - a) / gRatio;

		int iter = 0;
		while (abs(c - d) > tolerance) {
			matrix3x3 Rsc;
			vec3 biasc;
			real fc;
			matrix3x3 Rsd;
			vec3 biasd;
			real fd;
			fc = register_directions(angVis, angImu, t, c, Rsc, biasc);
			fd = register_directions(angVis, angImu, t, d, Rsd, biasd);

			if (fc < fd) {
				b = d;
				Rs = Rsc;
				bg = biasc;
			}
			else {
				a = c;
				Rs = Rsd;
				bg = biasd;
			}

			c = b - (b - a) / gRatio;
			d = a + (b - a) / gRatio;

			iter = iter + 1;
		}
		td = (b + a) / 2;
	}

	void lti_disc(Eigen::MatrixXd& F, Eigen::MatrixXd& L, real qc, real dt, Eigen::MatrixXd&A, Eigen::MatrixXd&Q)
	{
		A = (F*dt).exp();
		int n = F.rows();
		Eigen::MatrixXd phi(n * 2, n * 2);
		phi.setZero();
		phi.block(0, 0, n, n * 2) << F, L*qc*L.transpose();
		Eigen::MatrixXd fill(n * 2, n);
		fill.setZero();
		for (int i = 0; i < n; i++) {
			phi(n + i, n + i) = 0.0;
			fill(n + i, i) = 1.0;
		}
		phi.block(n, n, n, n) << -(F.transpose());

		Eigen::MatrixXd AB = (phi*dt).exp()*fill;
		Eigen::MatrixXd AA = AB.block(0, 0, n, n);
		Eigen::MatrixXd BB = AB.block(n, 0, n, n);
		Q = AA * BB.inverse();
	}

	std::vector<vec3> kalman_rts(const std::vector<vec3>& pos, const std::vector<real>& t)
	{
		std::vector<vec3> acc;
		
		real dt = mean(diff(t));
		Eigen::MatrixXd F(3,3);
		F << 0, 1, 0,
			0, 0, 1,
			0, 0, 0;
		real R = 0.1*0.1;
		Eigen::MatrixXd L(3,1);
		L << 0, 0, 1;
		Eigen::MatrixXd H(1, 3);
		H << 1, 0, 0;
		Eigen::MatrixXd m0(3, 1);
		m0 << 0, 0, 0;
		Eigen::MatrixXd P0(3, 3);
		P0 << 1, 0, 0,
			0, 1, 0,
			0, 0, 1;
		P0 = P0 * 10000.0;
		std::vector<real> qc_list;
		for (int i = 45; i < 130; i += 10) {
			qc_list.push_back(i);
		}
		std::vector<real> lh_list(qc_list.size(), 0);

		for (int j = 1; j <= qc_list.size(); j++) {
			real qc = qc_list[j - 1];
			Eigen::MatrixXd A, Q;
			lti_disc(F, L, qc, dt, A, Q);
			real lh = 0;
			for (int i = 0; i < vec3::n; i++) {
				Eigen::MatrixXd m = m0;
				Eigen::MatrixXd P = P0;
				for (int k = 0; k < pos.size(); k++) {
					m = A * m;
					P = A * P*A.transpose() + Q;
					real nu = pos[k][i] - (H*m)(0);
					real S = (H * P*H.transpose())(0) + R;
					Eigen::MatrixXd K = P * H.transpose() / S;
					m = m + K * nu;
					P = P - K * S*K.transpose();
					lh = lh + 0.5*::log(2 * M_PI) + 0.5*::log(S);
					lh += 0.5*nu*nu/S;
				}

			}
			lh_list[j - 1] = lh;
		}

		real qc;
		real min_idx = -1;
		real min_val = 10000000000.0;
		for (int i = 0; i < lh_list.size(); i++) {
			if (lh_list[i] < min_val) {
				min_val = lh_list[i];
				min_idx = i;
			}
		}

		qc = qc_list[min_idx];

		std::vector<vec3> pos_kfs(pos.size(), vec3(0));
		std::vector<vec3> vel_kfs(pos.size(), vec3(0));
		std::vector<vec3> acc_kfs(pos.size(), vec3(0));


		Eigen::MatrixXd A, Q;
		lti_disc(F, L, qc, dt, A, Q);

		for (int i = 0; i < vec3::n; i++) {

			// Kalman filter
			Eigen::MatrixXd m = m0;
			Eigen::MatrixXd P = P0;
			Eigen::MatrixXd kf_m(m.rows(), pos.size());
			kf_m.setZero();
			std::vector<Eigen::MatrixXd> kf_P(pos.size());
			for (int k = 0; k < pos.size(); k++) {
				m = A * m;
				P = A * P*A.transpose() + Q;
				real y = pos[k][i] - (H*m)(0);
				real S = (H * P*H.transpose())(0) + R;
				Eigen::MatrixXd K = P * H.transpose() / S;
				m = m + K * y;
				P = P - K * S*K.transpose();

				kf_m.block(0, k, m.rows(), m.cols()) = m;
				kf_P[k] = P;
			}

			// RTS smoother
			Eigen::MatrixXd ms = m;
			Eigen::MatrixXd Ps = P;
			Eigen::MatrixXd rts_m(m.rows(), pos.size());
			rts_m.setZero();
			rts_m.block(0, pos.size() - 1, ms.rows(), ms.cols()) = ms;
			for (int k = kf_m.cols() - 2; k >= 0; k--) {
				Eigen::MatrixXd mp = A * kf_m.block(0, k, m.rows(), m.cols());
				Eigen::MatrixXd Pp = A * kf_P[k]*A.transpose()+Q;    
				Eigen::MatrixXd Ck = kf_P[k]*A.transpose()*Pp.inverse(); 
				ms = kf_m.block(0, k, m.rows(), m.cols()) + Ck * (ms - mp);
				Ps = kf_P[k] + Ck * (Ps - Pp)*Ck.transpose();
				rts_m.block(0, k, ms.rows(), ms.cols()) = ms;
			}

			for (int k = 0; k < pos.size(); k++) {
				pos_kfs[k][i] = rts_m(0, k);
				vel_kfs[k][i] = rts_m(1, k);
				acc_kfs[k][i] = rts_m(2, k);
			}

		}

		acc = acc_kfs;
		return acc;
	}


	struct my_opt_data {
		Eigen::MatrixXd* A;
		Eigen::MatrixXd* b;
		std::vector<bool>* freqRange;

	};
	

	static real opt_func(unsigned n, const real *xx, real *grad, void *my_func_data)
	{
		my_opt_data& dat = *((my_opt_data*)my_func_data);
		Eigen::MatrixXd& A = *dat.A;
		Eigen::MatrixXd& b = *dat.b; 
		std::vector<bool>& freqRange = *dat.freqRange;
		Eigen::MatrixXd x(4,1);
		for (int i = 0; i < 4; i++) x(i) = xx[i];

		Eigen::MatrixXd Av = A * x;// Visual accelerations
		Eigen::MatrixXd Ai = b;    // Inertial accelerations
		Eigen::MatrixXd AAv(Av.size() / 3, 3);
		Eigen::MatrixXd AAi(Ai.size() / 3, 3);

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < AAv.rows(); j++) {
				AAv(j, i) = Av(i + j * 3);
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < AAi.rows(); j++) {
				AAi(j, i) = Ai(i + j * 3);
			}
		}

		int N = AAv.rows();
		Eigen::MatrixXd FFTR(AAv.rows(), AAv.rows());
		Eigen::MatrixXd FFTi(AAv.rows(), AAv.rows());

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				FFTR(i, j) = cos(2.0*M_PI*real(i)*real(j) / real(N));
				FFTi(i, j) = sin(2.0*M_PI*real(i)*real(j) / real(N));
			}
		}

		Eigen::MatrixXd AAvR(AAv.rows(), AAv.cols());
		Eigen::MatrixXd AAvi(AAv.rows(), AAv.cols());
		AAvR = FFTR * AAv;
		AAvi = FFTi * AAv;

		for (int i = 0; i < AAvR.rows(); i++) {
			for (int j = 0; j < AAvR.cols(); j++) {
				AAv(i, j) = sqrt((AAvR(i, j)*AAvR(i, j) + AAvi(i, j)*AAvi(i, j)));
			}
		}
		Eigen::MatrixXd AivR(AAi.rows(), AAi.cols());
		Eigen::MatrixXd Aivi(AAv.rows(), AAi.cols());
		AivR = FFTR * AAi;
		Aivi = FFTi * AAi;
		for (int i = 0; i < AAvR.rows(); i++) {
			for (int j = 0; j < AAvR.cols(); j++) {
				AAi(i, j) = sqrt((AivR(i, j)*AivR(i, j) + Aivi(i, j)*Aivi(i, j)));
			}
		}
		real sum = 0;
		for (int i = 0; i < freqRange.size(); i++) {
			if (freqRange[i]) {
				int cols = AAv.cols();
				for (int j = 0; j < cols; j++) {
					real tmp = AAv(i, j) - AAi(i, j);
					tmp = tmp * tmp;
					sum += tmp;
				}
			}
		}
	
		if (grad) {
			// now compute gradient
			Eigen::MatrixXd CAAvR(AAv.rows(), AAv.cols());
			Eigen::MatrixXd CAAvi(AAv.rows(), AAv.cols());
			CAAvR.setZero();
			CAAvi.setZero();						
			for (int i = 0; i < freqRange.size(); i++) {
				if (freqRange[i]) {
					int cols = AAv.cols();
					for (int j = 0; j < cols; j++) {
						real tmp = AAv(i, j) - AAi(i, j);

						CAAvR(i, j) = 1 / AAv(i, j)*tmp*2.0*AAvR(i, j);
						CAAvi(i, j) = 1 / AAv(i, j)*tmp*2.0*AAvi(i, j);
					}
				}
			}
			FFTR = FFTR.transpose();
			FFTi = FFTi.transpose();
			CAAvR = FFTR*CAAvR;
			CAAvR = CAAvR + FFTi*CAAvi;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < AAv.rows(); j++) {
					Av(i + j * 3) = CAAvR(j, i);
				}
			}

			x = A.transpose()*Av;

			for (int i = 0; i < 4; i++)
				grad[i] = x(i);
		}
		LOG("function %f\n", sum);
		return sum;
	}
	
	real estimateScale(const std::vector<vec3>& accVis,
		const std::vector<vec4>&qtVis,
		const std::vector<vec3>& accImu,
		const std::vector<real>&  t,
		real& scale,
		vec3& bias)
	{
		int N = accVis.size();
		Eigen::MatrixXd A(3 * N, 4);
		Eigen::MatrixXd b(3 * N, 1);
		A.setZero();
		b.setZero();

		for (int n = 0; n < N; n++)
		{
			A(n * 3, 0) = accVis[n][0];
			A(n * 3 + 1, 0) = accVis[n][1];
			A(n * 3 + 2, 0) = accVis[n][2];
			A(n * 3, 1) = 1.0;
			A(n * 3 + 1, 2) = 1.0;
			A(n * 3 + 2, 3) = 1.0;
			b(n * 3, 0) = accImu[n][0];
			b(n * 3 + 1, 0) = accImu[n][1];
			b(n * 3 + 2, 0) = accImu[n][2];
		}

		Eigen::MatrixXd x = A.bdcSvd(Eigen::ComputeFullU | Eigen::ComputeFullV).solve(b);
		real scale0;
		vec3 bias0;
		scale0 = x(0);
		bias0 = vec3(x(1), x(2), x(3));

		N = t.size();
		real fmax = 1.2;
		real fs = 1 / mean(diff(t));
		int ss = N / 2 + 1;
		std::vector<bool> freqRange;
		for (int i = 0; i < ss; i++) {
			freqRange.push_back(fs*real(i) / real(N) <= fmax);
		}

		nlopt_opt opt;
		my_opt_data data;
		data.A = &A;
		data.b = &b;
		data.freqRange = &freqRange;

		opt = nlopt_create(NLOPT_LD_AUGLAG_EQ, 4);
		nlopt_opt sub_opt = nlopt_create(NLOPT_LD_LBFGS, 4);
		nlopt_set_min_objective(opt, opt_func, &data);
		nlopt_set_xtol_rel(opt, 1e-7);
		nlopt_set_min_objective(sub_opt, opt_func, &data);
		nlopt_set_xtol_rel(sub_opt, 1e-7);
		nlopt_set_local_optimizer(opt, sub_opt);

		real sol[4];
		for (int i = 0; i < 4; i++)
		sol[i] = x(i);

		real minf;
		if (nlopt_optimize(opt, sol, &minf) < 0) {
			nlopt_destroy(opt);
		}
		else
		{
		}
		
		scale = sol[0];
		bias = vec3(sol[1], sol[2], sol[3]);
		nlopt_destroy(opt);
		nlopt_destroy(sub_opt);
		return minf;
	}
};
