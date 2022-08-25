#include "graphics/image_sample.h"
#include <algorithm>

namespace graphics {

#define IMAGE_VAL(x,y,c,w,n,mem) (mem[x*n + y*w*n + c])

	vec3 image_sample(float xx, float yy, int c, size_t w, size_t h, float* in)
	{
		int x1 = (int)floor(xx);
		int x2 = (int)ceil(xx);
		int y1 = (int)floor(yy);
		int y2 = (int)ceil(yy);

		if (x1 < 0 || x1 >= w /*|| x2 < 0 || x2 >= w*/) return vec3(0);
		if (y1 < 0 || y1 >= h /*|| y2 < 0 || y2 >= h*/) return vec3(0);
		if (x2 >= w) {
			x2 = w - 1; xx = floor(xx);
		}
		if (y2 >= h) {
			y2 = h - 1; yy = floor(yy);
		}
		vec3 ret(0);
		float v1, v2, v3, v4, tvx, tvy;

		tvx = xx - floor(xx);
		tvy = yy - floor(yy);
		int tc = std::min(c, ret.n);
		for (int i = 0; i < tc; i++) {
			v1 = IMAGE_VAL(x1, y1, i, w, c, in);
			v2 = IMAGE_VAL(x2, y1, i, w, c, in);
			v3 = IMAGE_VAL(x1, y2, i, w, c, in);
			v4 = IMAGE_VAL(x2, y2, i, w, c, in);
			v1 = (1.0 - tvx)*v1 + tvx * v2;
			v3 = (1.0 - tvx)*v3 + tvx * v4;
			v1 = (1.0 - tvy)*v1 + tvy * v3;

			ret[i] = v1;
		}

		return ret;
	}

	vec3 image_sample(float xx, float yy, int c, size_t w, size_t h, unsigned char* in)
	{
		int x1 = (int)floor(xx);
		int x2 = (int)ceil(xx);
		int y1 = (int)floor(yy);
		int y2 = (int)ceil(yy);

		if (x1 < 0 || x1 >= w /*|| x2 < 0 || x2 >= w*/) return vec3(0);
		if (y1 < 0 || y1 >= h /*|| y2 < 0 || y2 >= h*/) return vec3(0);
		if (x2 >= w) {
			x2 = w - 1; xx = floor(xx);
		}
		if (y2 >= h) {
			y2 = h - 1; yy = floor(yy);
		}

		vec3 ret(0);
		float v1, v2, v3, v4, tvx, tvy;

		tvx = xx - floor(xx);
		tvy = yy - floor(yy);

		int tc = std::min(c, ret.n);
		for (int i = 0; i < tc; i++) {
			v1 = IMAGE_VAL(x1, y1, i, w, c, in);
			v2 = IMAGE_VAL(x2, y1, i, w, c, in);
			v3 = IMAGE_VAL(x1, y2, i, w, c, in);
			v4 = IMAGE_VAL(x2, y2, i, w, c, in);
			v1 = (1.0 - tvx)*v1 + tvx * v2;
			v3 = (1.0 - tvx)*v3 + tvx * v4;
			v1 = (1.0 - tvy)*v1 + tvy * v3;

			ret[i] = v1;
		}

		return ret;
	}

	vec4 image_sample_vec4(float xx, float yy, int c, size_t w, size_t h, unsigned char* in)
	{
		int x1 = (int)floor(xx);
		int x2 = (int)ceil(xx);
		int y1 = (int)floor(yy);
		int y2 = (int)ceil(yy);

		if (x1 < 0 || x1 >= w /*|| x2 < 0 || x2 >= w*/) return vec4(0);
		if (y1 < 0 || y1 >= h /*|| y2 < 0 || y2 >= h*/) return vec4(0);
		if (x2 >= w) {
			x2 = w - 1; xx = floor(xx);
		}
		if (y2 >= h) {
			y2 = h - 1; yy = floor(yy);
		}

		vec4 ret(0);
		float v1, v2, v3, v4, tvx, tvy;

		tvx = xx - floor(xx);
		tvy = yy - floor(yy);

		int tc = std::min(c, ret.n);
		for (int i = 0; i < tc; i++) {
			v1 = IMAGE_VAL(x1, y1, i, w, c, in);
			v2 = IMAGE_VAL(x2, y1, i, w, c, in);
			v3 = IMAGE_VAL(x1, y2, i, w, c, in);
			v4 = IMAGE_VAL(x2, y2, i, w, c, in);
			v1 = (1.0 - tvx)*v1 + tvx * v2;
			v3 = (1.0 - tvx)*v3 + tvx * v4;
			v1 = (1.0 - tvy)*v1 + tvy * v3;

			ret[i] = v1;
		}

		return ret;
	}

	float image_sample(float xx, float yy, size_t w, size_t h, float* in)
	{
		int x1 = (int)floor(xx);
		int x2 = (int)ceil(xx);
		int y1 = (int)floor(yy);
		int y2 = (int)ceil(yy);

		if (x1 < 0 || x1 >= w /*|| x2 < 0 || x2 >= w*/) return 0;
		if (y1 < 0 || y1 >= h /*|| y2 < 0 || y2 >= h*/) return 0;
		if (x2 >= w) {
			x2 = w - 1; xx = floor(xx);
		}
		if (y2 >= h) {
			y2 = h - 1; yy = floor(yy);
		}

		vec3 ret(0);
		float v1, v2, v3, v4, tvx, tvy;

		tvx = xx - floor(xx);
		tvy = yy - floor(yy);

		v1 = IMAGE_VAL(x1, y1, 0, w, 1, in);
		v2 = IMAGE_VAL(x2, y1, 0, w, 1, in);
		v3 = IMAGE_VAL(x1, y2, 0, w, 1, in);
		v4 = IMAGE_VAL(x2, y2, 0, w, 1, in);
		v1 = (1.0 - tvx)*v1 + tvx * v2;
		v3 = (1.0 - tvx)*v3 + tvx * v4;
		v1 = (1.0 - tvy)*v1 + tvy * v3;

		return v1;
	}

}