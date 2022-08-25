#include <graphics/gauss_dist_im.h>
namespace graphics {

	void gauss_dist_im_2d(float* img, int w, int h, const vec2& center, double sigma)
	{
		double s = 2.0 * sigma * sigma;
		double sum = 0;
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				vec2 pos(x, y);
				double r = norm(pos - center);
				double t = (exp(-(r * r) / s)) / (M_PI * s);
				img[x + y * w] = t;
				sum += t;
			}
		}
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				img[x + y * w] /= sum;
			}
		}
	}
	void gauss_dist_im_2d_strengthened(float* img, int w, int h, const vec2& center, double sigma, double squash)
	{
		double s = 2.0 * sigma * sigma;
		double max_v = 0;
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				vec2 pos(x, y);
				double r = norm(pos - center);
				double t = (exp(-(r * r) / s)) / (M_PI * s);
				img[x + y * w] = t;
				max_v = max_v<t?t:max_v;
			}
		}
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				img[x + y * w] = img[x + y * w]/max_v * squash;
			}
		}
	}

	void circle_dist(float* img, int w, int h, const vec2& center, double sigma, double squash)
	{
		double s = 2.0 * sigma * sigma;
		double max_v = 0;
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				vec2 pos(x, y);
				double r = norm(pos - center);
				double t = r < sigma ? 1 : 0;//(exp(-(r * r) / s)) / (M_PI * s);
				img[x + y * w] = t;
				max_v = max_v < t ? t : max_v;
			}
		}
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				img[x + y * w] = img[x + y * w] / max_v * squash;
			}
		}
	}
}