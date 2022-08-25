// Copyright (c) 2009 libmv authors.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#include "graphics/vision_camera.h"
#include "graphics/matrix4x4.h"

namespace graphics {

	void P_From_KRt(const matrix3x3 &K, const matrix3x3 &R, const vec3 &t, matrix3x4 *P) {
		P->set(R);
		P->set_col(3, R * t * -1);
		(*P) = K * (*P);
	}

	bool KRt_From_P(const matrix3x4 &P, matrix3x3 *Kp, matrix3x3 *Rp, vec3 *tp) {

		matrix3x3 t1;
		t1.set_col(0, P.col(1));
		t1.set_col(1, P.col(2));
		t1.set_col(2, P.col(3));
		real x_ = t1.determinant();
		t1.set_col(0, P.col(0));
		t1.set_col(1, P.col(2));
		t1.set_col(2, P.col(3));
		real y_ = -t1.determinant();
		t1.set_col(0, P.col(0));
		t1.set_col(1, P.col(1));
		t1.set_col(2, P.col(3));
		real z_ = t1.determinant();
		t1.set_col(0, P.col(0));
		t1.set_col(1, P.col(1));
		t1.set_col(2, P.col(2));
		real w_ = -t1.determinant();

		(*tp)(0) = x_ / w_;
		(*tp)(1) = y_ / w_;
		(*tp)(2) = z_ / w_;


		// Decompose using the RQ decomposition HZ A4.1.1 pag.579.
		matrix3x3 K;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				K(i, j) = P(i, j);

		matrix3x3 Q;
		Q.makeIdentity();

		// Set K(2,1) to zero.
		if (K(2, 1) != 0) {
			real c = -K(2, 2);
			real s = K(2, 1);
			real l = sqrt(c * c + s * s);
			c /= l; s /= l;
			matrix3x3 Qx(1, 0, 0,
				0, c, -s,
				0, s, c);
			K = K * Qx;
			Q = Qx.get_transpose() * Q;
		}
		// Set K(2,0) to zero.
		if (K(2, 0) != 0) {
			real c = K(2, 2);
			real s = K(2, 0);
			real l = sqrt(c * c + s * s);
			c /= l; s /= l;
			matrix3x3 Qy(c, 0, s,
				0, 1, 0,
				-s, 0, c);
			K = K * Qy;
			Q = Qy.get_transpose() * Q;
		}
		// Set K(1,0) to zero.
		if (K(1, 0) != 0) {
			real c = -K(1, 1);
			real s = K(1, 0);
			real l = sqrt(c * c + s * s);
			c /= l; s /= l;
			matrix3x3 Qz(c, -s, 0,
				s, c, 0,
				0, 0, 1);
			K = K * Qz;
			Q = Qz.get_transpose() * Q;
		}

		matrix3x3 R = Q;


		if (K(2, 2) < 0) {
			K = K * -1;
			R = R * -1;
		}
		if (K(1, 1) < 0) {
			matrix3x3 S(1, 0, 0,
				0, -1, 0,
				0, 0, 1);
			K = K * S;
			R = S * R;
		}
		if (K(0, 0) < 0) {
			matrix3x3 S(-1, 0, 0,
				0, 1, 0,
				0, 0, 1);
			K = K * S;
			R = S * R;
		}


		*Kp = K;
		*Rp = R;

		return true;


	}
	VisionCamera::VisionCamera():skew_factor_(0) {
		orientation_matrix_.makeIdentity();
		intrinsic_matrix_.makeIdentity();
		UpdateProjectionMatrix();
	}

	VisionCamera::VisionCamera(const matrix3x4  &P) :skew_factor_(0) {
		set_projection_matrix(P);
	}

	VisionCamera::VisionCamera(const matrix3x3  &R, const vec3  &t) : skew_factor_(0) {
		orientation_matrix_ = R;
		position_ = t;
		UpdateProjectionMatrix();
	}

	VisionCamera::VisionCamera(const matrix3x3  &K,
		const matrix3x3  &R,
		const vec3  &t) :skew_factor_(0) {
		intrinsic_matrix_ = K;
		orientation_matrix_ = R;
		position_ = t;

		UpdateProjectionMatrix();
	}
	VisionCamera::VisionCamera(real focal,
		const vec2 &principal_point) :skew_factor_(0) {
		orientation_matrix_.makeIdentity();
		SetIntrinsicParameters(focal, principal_point);
	}
	VisionCamera::VisionCamera(int w, int h) : skew_factor_(0)
	{
		orientation_matrix_.makeIdentity();
		position_ = vec3(0);
		vec2 p(w / 2, h / 2);
		SetIntrinsicParameters(w, p);
		set_image_size(w, h);
	}
	VisionCamera::~VisionCamera() {
	}

	VisionCamera::VisionCamera(const VisionCamera &camera) 
		:skew_factor_(camera.skew_factor_) {
		this->set_intrinsic_matrix(camera.intrinsic_matrix());
		this->SetExtrinsicParameters(camera.orientation_matrix(), camera.position());
		image_size_ = camera.image_size();
	}
	 
	matrix4x4 VisionCamera::ogl_projection_matrix(float n, float f) const
	{
		double L = 0;
		double R = image_size_[0];
		double B = 0;
		double T = image_size_[1];
		double N = n;
		double F = f;
		matrix4x4 ortho;
		ortho.setZero();
		ortho(0, 0) = 2.0 / (R - L); ortho(0, 3) = -(R + L) / (R - L);
		ortho(1, 1) = 2.0 / (T - B); ortho(1, 3) = -(T + B) / (T - B);
		ortho(2, 2) = -2.0 / (F - N); ortho(2, 3) = -(F + N) / (F - N);
		ortho(3, 3) = 1.0;
		matrix4x4 tproj;
		tproj.setZero();
		tproj(0, 0) = intrinsic_matrix_(0, 0);
		tproj(0, 1) = intrinsic_matrix_(0, 1);
		tproj(0, 2) = intrinsic_matrix_(0, 2);
		tproj(1, 1) = intrinsic_matrix_(1, 1); ;
		tproj(1, 2) = intrinsic_matrix_(1, 2); ;
		tproj(2, 2) = -(N + F); tproj(2, 3) = -N * F;
		tproj(3, 2) = 1.0;
		matrix4x4 tmp = ortho * tproj;
		tmp(2, 2) *= -1;
		tmp(3, 2) *= -1;
		tmp(2, 3) *= -1;
		//tmp(0, 1) *= -1;
		tmp(0, 2) *= -1;
		//tmp(1, 1) *= -1;

		tmp.transpose();
		return tmp;
	}
	vec3 VisionCamera::to_model(const vec3& p)
	{
		graphics::matrix3x4 prj;
		prj.set(orientation_matrix_);
		prj.set_col(3, orientation_matrix_ * position_ * -1);
		vec4 pp(p[0], p[1], p[2], 1);
		vec3 ret = prj * pp;
		return ret;
	}
	vec3 VisionCamera::to_world(const vec3& p)
	{
		matrix3x4 prj = GetPoseMatrix();
		vec4 pp(p[0], p[1], p[2], 1);
		vec3 ret = prj * pp;
		return ret;
	}
	vec3 VisionCamera::to_world_normal(const vec3& p)
	{
		matrix3x3 ora = orientation_matrix_;
		ora.transpose();
		vec3 pp(p[0], p[1], p[2]);
		vec3 ret = ora *pp;
		return ret;
	}
	line VisionCamera::to_world(const line& r)
	{
		matrix3x4 prj = GetPoseMatrix();
		vec3 p1 = r.get_position();
		vec3 p2 = r.get_position() + r.get_direction();
		vec4 pp1(p1[0], p1[1], p1[2], 1);
		vec4 pp2(p2[0], p2[1], p2[2], 1);
		p1 = prj * pp1;
		p2 = prj * pp2;
		return line(p1, p2);

	}
	line VisionCamera::ray(const vec2& p)
	{
		matrix3x3 inv_i = intrinsic_matrix_.inverse();
		vec3 pp(p[0], p[1], 1.0);
		pp = inv_i * pp;
		return line(vec3(0), vec3(pp));
	}

	// The function computes updates the projection matrix from intrinsic
	// parameters (focal,...).
	void VisionCamera::UpdateIntrinsicMatrix() {
		intrinsic_matrix_ = matrix3x3(focal_x_, skew_factor_, principal_point_(0),
			0, focal_y_, principal_point_(1),
			0, 0, 1);
		UpdateProjectionMatrix();
	}

	// The function updates the projection matrix from intrinsic and
	// extrinsic parameters.
	void VisionCamera::UpdateProjectionMatrix() {
		P_From_KRt(intrinsic_matrix_,
			orientation_matrix_,
			position_,
			&projection_matrix_);
		focal_x_ = intrinsic_matrix_(0, 0) / intrinsic_matrix_(2, 2);
		focal_y_ = intrinsic_matrix_(1, 1) / intrinsic_matrix_(2, 2);
		skew_factor_ = intrinsic_matrix_(0, 1) / intrinsic_matrix_(2, 2);
		principal_point_(0) = intrinsic_matrix_(0, 2) / intrinsic_matrix_(2, 2);
		principal_point_(1) = intrinsic_matrix_(1, 2) / intrinsic_matrix_(2, 2);
	}


	vec2 VisionCamera::project_point(const vec3& p)
	{
		vec2 ret;
		vec4 in(p[0], p[1], p[2], 1);
		Project(projection_matrix_, in, &ret);
		return ret;
	}
}  // namespace libmv
