#ifndef __DistortionFunction_h
#define __DistortionFunction_h

#include <QtGui/qimage.h>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <graphics/vec.h>


namespace user {


class DistortionFunction
{
	cv::Mat distCoeffs_;
	cv::Mat cameraMatrix_;
	cv::Mat map1x, map1y;
	cv::Mat imap1x, imap1y;
	float* invmap1x, *invmap1y;

	int width_, height_;

public:
	DistortionFunction();
	void init(cv::Mat& cam, cv::Mat& dist, int w, int h);
	DistortionFunction(cv::Mat& cam, cv::Mat& dist, int w, int h);
	~DistortionFunction() {}

	void undistort(QImage& im);

	void distort(QImage& im);
	graphics::vec2 undistort_point(graphics::vec2 in)
	{
		std::vector< cv::Point2f > contour2f(1);
		contour2f[0].x = in[0];
		contour2f[0].y = in[1];
		cv::undistortPoints(contour2f, contour2f, cameraMatrix_, distCoeffs_, cv::Mat(), cameraMatrix_);
		return graphics::vec2(contour2f[0].x, contour2f[0].y);
	}

	graphics::vec2 undistort_point_by_map(graphics::vec2 in);
	graphics::vec2 distort_point_by_map(graphics::vec2 in);

private:
	void compute_inverse_map(cv::Mat& mat_x, cv::Mat& mat_y,
		cv::Mat& inv_mat_x, cv::Mat&inv_mat_y);

	

	

};

}

#endif