#include <DistortionFunction.h>
#include <graphics/vec.h>
#include <graphics/geom.h>
#include <graphics/barycentric.h>
using namespace graphics;
namespace user {
#define kepco_min(a,b) (a<b?a:b)
#define kepco_max(a,b) (a>b?a:b)
	inline float _interpolate(
		float x,
		float y,
		cv::Mat& img,
		int w,
		int h)
	{
		x = kepco_min(kepco_max(x, 0), w - 2);
		y = kepco_min(kepco_max(y, 0), h - 2);

		int xt = (int)x;
		int yt = (int)y;
		float ax = x - xt;
		float ay = y - yt;
		int stride = img.step / sizeof(float);
		float *ptr = (float*)img.data + (stride*yt) + xt;

		return ((1 - ax) * (1 - ay) * *ptr +
			ax * (1 - ay) * *(ptr + 1) +
			(1 - ax) *   ay   * *(ptr + stride) +
			ax * ay   * *(ptr + stride + 1));
	}
void DistortionFunction::compute_inverse_map(cv::Mat& mat_x, cv::Mat& mat_y, 
	cv::Mat& inv_mat_x, cv::Mat&inv_mat_y)
{
	inv_mat_x = mat_x.clone();
	inv_mat_y = mat_y.clone();

	int w = mat_x.cols, h = mat_x.rows;

	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			inv_mat_x.at<float>(y, x) = -1;
			inv_mat_y.at<float>(y, x) = -1;
		}
	}

	for (int y = 1; y < h; y++) {
		for (int x = 0; x < w - 1; x++) {
			vec2 p1(mat_x.at<float>(y - 1, x), mat_y.at<float>(y - 1, x));
			vec2 p2(mat_x.at<float>(y - 1, x + 1), mat_y.at<float>(y - 1, x + 1));
			vec2 p3(mat_x.at<float>(y, x), mat_y.at<float>(y, x));
			vec2 p4(mat_x.at<float>(y, x + 1), mat_y.at<float>(y, x + 1));
			float v1 = x;
			float v2 = x + 1;
			float v3 = x;
			float v4 = x + 1;
			float vv1 = y - 1;
			float vv2 = y - 1;
			float vv3 = y;
			float vv4 = y;
			box2 box;
			box.extend(p1);
			box.extend(p2);
			box.extend(p3);
			box.extend(p4);
			int xs = kepco_min(w - 1, kepco_max(0, floor(box.minimum[0])));
			int xe = kepco_min(w - 1, kepco_max(0, ceil(box.maximum[0])));
			int ys = kepco_min(h - 1, kepco_max(0, floor(box.minimum[1])));
			int ye = kepco_min(h - 1, kepco_max(0, ceil(box.maximum[1])));
			for (int xx = xs; xx <= xe; xx++) {
				for (int yy = ys; yy <= ye; yy++) {
					vec3 bcoord = barycentric_coordinate(p1, p2, p3, vec2(xx, yy));
					if (bcoord[0] >= 0.0 - zero_epsilon && bcoord[0] <= 1.0 + zero_epsilon
						&& bcoord[1] >= 0.0 - zero_epsilon && bcoord[1] <= 1.0 + zero_epsilon
						&& bcoord[2] >= 0.0 - zero_epsilon && bcoord[2] <= 1.0 + zero_epsilon)
					{
						float v = v1 * bcoord[0] + v2 * bcoord[1] + v3 * bcoord[2];
						inv_mat_x.at<float>(yy, xx) = v;
						v = vv1 * bcoord[0] + vv2 * bcoord[1] + vv3 * bcoord[2];
						inv_mat_y.at<float>(yy, xx) = v;
						continue;
					}
					bcoord = barycentric_coordinate(p2, p3, p4, vec2(xx, yy));
					if (bcoord[0] >= 0.0 - zero_epsilon && bcoord[0] <= 1.0 + zero_epsilon
						&& bcoord[1] >= 0.0 - zero_epsilon && bcoord[1] <= 1.0 + zero_epsilon
						&& bcoord[2] >= 0.0 - zero_epsilon && bcoord[2] <= 1.0 + zero_epsilon)
					{
						float v = v2 * bcoord[0] + v3 * bcoord[1] + v4 * bcoord[2];
						inv_mat_x.at<float>(yy, xx) = v;
						v = vv1 * bcoord[0] + vv2 * bcoord[1] + vv3 * bcoord[2];
						inv_mat_y.at<float>(yy, xx) = v;
						continue;
					}
				}
			}
		}
	}
}
DistortionFunction::DistortionFunction()
	: cameraMatrix_(), distCoeffs_(), width_(0), height_(0)
{

}
DistortionFunction::DistortionFunction(cv::Mat& cam, cv::Mat& dist, int w, int h)
{
	init(cam, dist, w, h);
}

void DistortionFunction::init(cv::Mat& cam, cv::Mat& dist, int w, int h)
{
	cameraMatrix_ = cam.clone();
	distCoeffs_ = dist.clone();
	width_ = w;
	height_ = h;
	initUndistortRectifyMap(cameraMatrix_, distCoeffs_, cv::Mat(), cameraMatrix_, cv::Size(w, h), CV_32FC1, map1x, map1y);
	compute_inverse_map(map1x, map1y, imap1x, imap1y);

}
vec2 DistortionFunction::undistort_point_by_map(vec2 in)
{
	float v1= _interpolate(in[0], in[1], imap1x, width_, height_);
	float v2 = _interpolate(in[0], in[1], imap1y, width_, height_);
	return vec2(v1, v2);
}
vec2 DistortionFunction::distort_point_by_map(vec2 in)
{
	float v1 = _interpolate(in[0], in[1], map1x, width_, height_);
	float v2 = _interpolate(in[0], in[1], map1y, width_, height_);
	return vec2(v1, v2);
	//return vec2(map1x.at<float>(in[1], in[0]), map1y.at<float>(in[1], in[0]));
}
void DistortionFunction::undistort(QImage& im)
{
	cv::Mat view = cv::Mat::zeros(im.height(), im.width(), CV_8UC3);
	int w = im.width();
	int h = im.height();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			QRgb rgb = im.pixel(x, y);
			view.at<cv::Vec3b>(y, x) = cv::Vec3b(qBlue(rgb), qGreen(rgb), qRed(rgb));
		}
	}
	cv::Mat ret;

	remap(view, ret, map1x, map1y, cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			QRgb rgb = im.pixel(x, y);
			cv::Vec3b v = ret.at<cv::Vec3b>(y, x);
			im.setPixel(x, y, qRgb(v(2), v(1), v(0)));
		}
	}
}


void DistortionFunction::distort(QImage& im)
{
	cv::Mat view = cv::Mat::zeros(im.height(), im.width(), CV_8UC3);
	int w = im.width();
	int h = im.height();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			QRgb rgb = im.pixel(x, y);
			view.at<cv::Vec3b>(y, x) = cv::Vec3b(qBlue(rgb), qGreen(rgb), qRed(rgb));
		}
	}
	cv::Mat ret;

	remap(view, ret, imap1x, imap1y, cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			QRgb rgb = im.pixel(x, y);
			cv::Vec3b v = ret.at<cv::Vec3b>(y, x);
			im.setPixel(x, y, qRgb(v(2), v(1), v(0)));
		}
	}
}
}