#pragma once

#include <graphics/vec.h>

namespace graphics {

	void gauss_dist_im_2d(float* img, int w, int h, const vec2& center, double sigma);
	void gauss_dist_im_2d_strengthened(float* img, int w, int h, const vec2& center, double sigma, double squash);
	void circle_dist(float* img, int w, int h, const vec2& center, double sigma, double squash);
}