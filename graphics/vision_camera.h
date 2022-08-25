

#ifndef _vision_camera_h_
#define _vision_camera_h_



#include <graphics/matrix3x3.h>
#include <graphics/matrix3x4.h>
#include <graphics/matrix4x4.h>
#include <graphics/frame.h>


namespace graphics {
	void P_From_KRt(const matrix3x3 &K, const matrix3x3 &R, const vec3 &t, matrix3x4 *P);

	bool KRt_From_P(const matrix3x4 &P, matrix3x3 *Kp, matrix3x3 *Rp, vec3 *tp);

	inline void Project(const matrix3x4 &P, const vec4 &X, vec2 *x) {
		vec3 hx = P * X;
		*x = vec2(hx[0] / hx[2], hx[1] / hx[2]);
	}

	//
	// A pinhole camera model
	//
	// Equation of the projection of a 3D point in the camera frame:
	//  s x = K [ R | t ] X
	// where
	//  X is the homogeneous 3D point
	//  K is the calibration matrix with the intrinsic parameters.
	//  R is the orientation of the camera expressed in a world coordinate frame
	//  t is the position of the camera expressed in a world coordinate frame
	//  x is the 2D projection (pixel) of the homogeneous point X 
	//    in the camera frame
	//  s is a 2D scale factor
	//                             [ focal_x skew_factor principal_point_x]
	//  K can be decomposed in K = [    0      focal_y   principal_point_y]
	//                             [    0        0              1         ]
	//  where
	//    focal_x and focal_y are the camera focal (in pixels) along x and y axis
	//    principal_point_x and principal_point_y are the coordinate of the
	//      principal point (in pixels) expressed in the camera frame
	//
	class VisionCamera {
	public:
		VisionCamera();
		VisionCamera(const matrix3x4  &P);
		VisionCamera(const matrix3x3  &R, const vec3  &t);
		VisionCamera(const matrix3x3  &K, const matrix3x3  &R, const vec3  &t);
		VisionCamera(real focal, const vec2 &principal_point);
		VisionCamera(int w, int h);
		virtual ~VisionCamera();

		vec2 project_point(const vec3& p);
		matrix4x4 ogl_projection_matrix(float n, float f) const;

		VisionCamera(const VisionCamera &camera);
		inline VisionCamera& operator=(const VisionCamera& camera)
		{
			this->set_intrinsic_matrix(camera.intrinsic_matrix());
			this->SetExtrinsicParameters(camera.orientation_matrix(), camera.position());
			image_size_ = camera.image_size();
			return *this;
		}
		const matrix3x4 &projection_matrix() const { return projection_matrix_; }
		const matrix3x3 &intrinsic_matrix() const { return intrinsic_matrix_; }
		const matrix3x3 &orientation_matrix() const { return orientation_matrix_; }
		const vec3 &position() const { return position_; }

		real focal_x() const { return focal_x_; }
		real focal_y() const { return focal_y_; }
		real skew_factor() const { return skew_factor_; }
		const vec2 &principal_point() const { return principal_point_; }
		const vec2 &image_size() const { return image_size_; }
		real image_width() const { return image_size_(0); }
		real image_height() const { return image_size_(1); }

		frame get_camera_frame() const {
			frame f(position_, vec3(orientation_matrix_(0, 0), orientation_matrix_(0, 1), orientation_matrix_(0, 2)), vec3(orientation_matrix_(1, 0), orientation_matrix_(1, 1), orientation_matrix_(1, 2)), vec3(orientation_matrix_(2, 0), orientation_matrix_(2, 1), orientation_matrix_(2, 2)));
			return f;

		}

		void get_look_at_matrix(float* A)
		{
			A[1] = 0;  A[2] = 0;  A[3] = 0;  A[4] = 0;
			A[6] = 0;  A[7] = 0;  A[8] = 0;  A[9] = 0;
			A[11] = 0;  A[12] = 0;  A[13] = 0;  A[14] = 0;
			A[0] = 1;
			A[5] = 1;
			A[10] = 1;
			A[15] = 1;

			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					real a = orientation_matrix_(i, j);
					A[j * 4 + i] = a;
				}
			}

			A[12] = -inner(position_, vec3(orientation_matrix_(0, 0), orientation_matrix_(0, 1), orientation_matrix_(0, 2)));
			A[13] = -inner(position_, vec3(orientation_matrix_(1, 0), orientation_matrix_(1, 1), orientation_matrix_(1, 2)));
			A[14] = -inner(position_, vec3(orientation_matrix_(2, 0), orientation_matrix_(2, 1), orientation_matrix_(2, 2)));

			A[1] *= -1.0;
			A[2] *= -1.0;
			A[5] *= -1.0;
			A[6] *= -1.0;
			A[9] *= -1.0;
			A[10] *= -1.0;
			A[13] *= -1.0;
			A[14] *= -1.0;
		}

		void transform(matrix4x4& tr)
		{
			vec3 v1 = tr.vtransform(vec3(orientation_matrix_(0, 0), orientation_matrix_(0, 1), orientation_matrix_(0, 2)));
			vec3 v2 = tr.vtransform(vec3(orientation_matrix_(1, 0), orientation_matrix_(1, 1), orientation_matrix_(1, 2)));
			vec3 v3 = tr.vtransform(vec3(orientation_matrix_(2, 0), orientation_matrix_(2, 1), orientation_matrix_(2, 2)));

			orientation_matrix_(0, 0) = v1[0];
			orientation_matrix_(0, 1) = v1[1];
			orientation_matrix_(0, 2) = v1[2];

			orientation_matrix_(1, 0) = v2[0];
			orientation_matrix_(1, 1) = v2[1];
			orientation_matrix_(1, 2) = v2[2];

			orientation_matrix_(2, 0) = v3[0];
			orientation_matrix_(2, 1) = v3[1];
			orientation_matrix_(2, 2) = v3[2];

			vec4 pp(position_[0], position_[1], position_[2], 1.0);
			pp = tr * pp;
			position_[0] = pp[0] / pp[3];
			position_[1] = pp[1] / pp[3];
			position_[2] = pp[2] / pp[3];

			UpdateProjectionMatrix();
		}
		vec3 x_dir() {
			return vec3(orientation_matrix_(0, 0), orientation_matrix_(0, 1), orientation_matrix_(0, 2));
		}
		vec3 y_dir() {
			return vec3(orientation_matrix_(1, 0), orientation_matrix_(1, 1), orientation_matrix_(1, 2));
		}
		vec3 z_dir() {
			return vec3(orientation_matrix_(2, 0), orientation_matrix_(2, 1), orientation_matrix_(2, 2));
		}

		vec3 to_model(const vec3& p);
		vec3 to_world(const vec3& p);
		vec3 to_world_normal(const vec3& p);
		line to_world(const line& r);
		line ray(const vec2& p);

		void set_projection_matrix(const matrix3x4 & p) {
			projection_matrix_ = p;
			// scale K so that K(2,2) = 1
			KRt_From_P(projection_matrix_,
				&intrinsic_matrix_,
				&orientation_matrix_,
				&position_);
			focal_x_ = intrinsic_matrix_(0, 0) / intrinsic_matrix_(2, 2);
			focal_y_ = intrinsic_matrix_(1, 1) / intrinsic_matrix_(2, 2);
			skew_factor_ = intrinsic_matrix_(0, 1) / intrinsic_matrix_(2, 2);
			principal_point_(0) = intrinsic_matrix_(0, 2) / intrinsic_matrix_(2, 2);
			principal_point_(1) = intrinsic_matrix_(1, 2) / intrinsic_matrix_(2, 2);
		}

		void set_intrinsic_matrix(const matrix3x3 &intrinsic_matrix) {
			intrinsic_matrix_ = intrinsic_matrix;
			focal_x_ = intrinsic_matrix_(0, 0) / intrinsic_matrix_(2, 2);
			focal_y_ = intrinsic_matrix_(1, 1) / intrinsic_matrix_(2, 2);
			skew_factor_ = intrinsic_matrix_(0, 1) / intrinsic_matrix_(2, 2);
			principal_point_(0) = intrinsic_matrix_(0, 2) / intrinsic_matrix_(2, 2);
			principal_point_(1) = intrinsic_matrix_(1, 2) / intrinsic_matrix_(2, 2);


			UpdateProjectionMatrix();
		}
		inline real degree(real rad) {
			return rad * (180 / M_PI);
		}

		float fov() {
			return degree(atan(intrinsic_matrix_(1, 2) / intrinsic_matrix_(0, 0))) * 2.0;
		}

		inline real radian(real deg)
		{
			return deg * (M_PI / 180);
		}

		void set_fov(float deg) {
			deg = deg / 2.0;
			float val = (1.0 / tan(radian(deg))) * intrinsic_matrix_(1, 2);
			intrinsic_matrix_(0, 0) = val;
			intrinsic_matrix_(1, 1) = val;
			UpdateProjectionMatrix();
		}
		void set_orientation_matrix(const matrix3x3 &orientation_matrix) {
			orientation_matrix_ = orientation_matrix;
			UpdateProjectionMatrix();
		}
		void set_position(const vec3 &position) {
			position_ = position;
			UpdateProjectionMatrix();
		}

		// TODO(julien) clean the code: avoid to have SetXXX and set_XXX
		void SetExtrinsicParameters(const matrix3x3 &orientation_matrix,
			const vec3 &position) {
			orientation_matrix_ = orientation_matrix;
			position_ = position;
			UpdateProjectionMatrix();
		}

		void SetExtrinsicParameters(const graphics::frame& f)
		{
			matrix3x3 ora = matrix3x3(f.basis[0][0], f.basis[0][1], f.basis[0][2],
				f.basis[1][0], f.basis[1][1], f.basis[1][2],
				f.basis[2][0], f.basis[2][1], f.basis[2][2]);
			SetExtrinsicParameters(ora, f.get_origin());
		}
		void SetIntrinsicParameters(real focal, const vec2 &principal_point) {
			focal_x_ = focal;
			focal_y_ = focal;
			principal_point_ = principal_point;
			UpdateIntrinsicMatrix();
			UpdateProjectionMatrix();
		}
		void SetIntrinsicParameters(real focal_x, real focal_y, real skew, vec2 principal_point) {
			focal_x_ = focal_x;
			focal_y_ = focal_y;
			skew_factor_ = skew;
			principal_point_ = principal_point;
			UpdateIntrinsicMatrix();
			UpdateProjectionMatrix();
		}
		void SetIntrinsicExtrinsicParameters(const matrix3x3 &intrinsic_matrix,
			const matrix3x3 &orientation_matrix,
			const vec3 &position) {
			intrinsic_matrix_ = intrinsic_matrix;
			focal_x_ = intrinsic_matrix_(0, 0);
			focal_y_ = intrinsic_matrix_(1, 1);
			principal_point_[0] = intrinsic_matrix_(0, 2);
			principal_point_[1] = intrinsic_matrix_(1, 2);
			orientation_matrix_ = orientation_matrix;
			position_ = position;
			UpdateProjectionMatrix();
		}
		void GetIntrinsicExtrinsicParameters(matrix3x3 *intrinsic_matrix,
			matrix3x3 *orientation_matrix,
			vec3 *position) {
			*intrinsic_matrix = intrinsic_matrix_;
			*orientation_matrix = orientation_matrix_;
			*position = position_;
		}
		void GetIntrinsicProjection(matrix3x3* intrinsic_matrix,
			matrix3x3 *orientation_matrix,
			vec3 *last_colum)
		{
			*intrinsic_matrix = intrinsic_matrix_;
			*orientation_matrix = orientation_matrix_;
			matrix3x4 pr = intrinsic_matrix_.inverse() * projection_matrix_;
			*last_colum = pr.col(3);
		}

		void SetIntrinsicProjection(const matrix3x3& intrinsic_matrix,
			const matrix3x3& orientation_matrix,
			const vec3& last_colum)
		{
			matrix3x4 pr;
			pr.setZero();
			pr.set(orientation_matrix);
			pr(0, 3) = last_colum[0];
			pr(1, 3) = last_colum[1];
			pr(2, 3) = last_colum[2];

			projection_matrix_ = (intrinsic_matrix)* pr;
			KRt_From_P(projection_matrix_,
				&intrinsic_matrix_,
				&orientation_matrix_,
				&position_);
			focal_x_ = intrinsic_matrix_(0, 0) / intrinsic_matrix_(2, 2);
			focal_y_ = intrinsic_matrix_(1, 1) / intrinsic_matrix_(2, 2);
			skew_factor_ = intrinsic_matrix_(0, 1) / intrinsic_matrix_(2, 2);
			principal_point_(0) = intrinsic_matrix_(0, 2) / intrinsic_matrix_(2, 2);
			principal_point_(1) = intrinsic_matrix_(1, 2) / intrinsic_matrix_(2, 2);
		}
		const matrix3x4 GetPoseMatrix() const {
			matrix3x4 P;
			matrix3x3 ora = orientation_matrix_;
			ora.transpose();

			P.set(ora);
			P.set_col(3, position_);
			return P; // P*a -> to world
		}
		void SetFocal(real focal) {
			focal_x_ = focal;
			focal_y_ = focal;
			UpdateIntrinsicMatrix();
			UpdateProjectionMatrix();
		}
		void SetFocal(real focal_x, real focal_y) {
			focal_x_ = focal_x;
			focal_y_ = focal_y;
			UpdateIntrinsicMatrix();
			UpdateProjectionMatrix();
		}
		void set_principal_point(const vec2 &principal_point) {
			principal_point_ = principal_point;
			UpdateIntrinsicMatrix();
			UpdateProjectionMatrix();
		}
		void set_skew_factor(real skew_factor) {
			skew_factor_ = skew_factor;
			UpdateIntrinsicMatrix();
			UpdateProjectionMatrix();
		}
		// Sets the image size (width, height)
		void set_image_size(const vec2 &size) {
			image_size_ = size;
		}
		void set_image_size(int w, int h)
		{
			image_size_[0] = w;
			image_size_[1] = h;
		}
	private:
		void UpdateProjectionMatrix();
		void UpdateIntrinsicMatrix();

		matrix3x4 projection_matrix_;
		matrix3x3  intrinsic_matrix_;
		matrix3x3  orientation_matrix_;
		vec3  position_;

		real  focal_x_;
		real  focal_y_;
		vec2    principal_point_;
		real  skew_factor_;
		// Contains the image size (width, height)
		vec2    image_size_;

	};


}  // namespace libmv

#endif  // LIBMV_CAMERA_PINHOLE_CAMERA_H_
