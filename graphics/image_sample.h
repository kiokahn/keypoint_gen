#pragma once
#include "graphics/vec.h"

namespace graphics
{
	// sample image "in" with w,h,c(channel) structure
	vec3 image_sample(float xx, float yy, int c, size_t w, size_t h, float* in);

	vec3 image_sample(float xx, float yy, int c, size_t w, size_t h, unsigned char* in);
	vec4 image_sample_vec4(float xx, float yy, int c, size_t w, size_t h, unsigned char* in);
	float image_sample(float xx, float yy, size_t w, size_t h, float* in);
}