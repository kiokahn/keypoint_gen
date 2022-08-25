#ifndef __seed_fill_h
#define __seed_fill_h

#include "graphics/geom.h"
#include <queue>
#include "graphics/ivec.h"

namespace graphics {

	template <typename T>
	void seed_fill(int x, int y, int w, int h, box2& roi, T* img, T new_pixel, T* reserve, T new_val, box2& out)
	{
		if (!roi.has_intersection(vec2(x, y))) return;
		if (img[x + y * w] == new_pixel) return;

		T val = img[x + y * w];
		std::queue<ivec2> cal_stack;
		img[x + y * w] = new_pixel;
		reserve[x + y * w] = new_val;

		out.extend(vec2(x, y));

		int nx, ny;
		nx = x - 1;
		ny = y - 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx,ny))) {
			cal_stack.push(ivec2(nx,ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}
		nx = x;
		ny = y - 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}
		nx = x+1;
		ny = y - 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}
		nx = x - 1;
		ny = y;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}
		nx = x + 1;
		ny = y;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}
		nx = x - 1;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}
		nx = x;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}
		nx = x + 1;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}
		
		while (cal_stack.size()) {
			ivec2 elem = cal_stack.front();
			cal_stack.pop();
			x = elem[0];
			y = elem[1];

			img[x + y * w] = new_pixel;
			reserve[x + y * w] = new_val;

			out.extend(vec2(x, y));

			nx = x - 1;
			ny = y - 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
			nx = x;
			ny = y - 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
			nx = x + 1;
			ny = y - 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
			nx = x - 1;
			ny = y;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
			nx = x + 1;
			ny = y;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
			nx = x - 1;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
			nx = x;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
			nx = x + 1;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
		}
	}
	template <typename T>
	int seed_fill(int x, int y, int w, int h, box2& roi, T* img, T new_pixel, box2& out)
	{
		if (!roi.has_intersection(vec2(x, y))) return 0;
		if (img[x + y * w] == new_pixel) return 0;

		int ret_cnt = 0;
		T val = img[x + y * w];
		std::queue<ivec2> cal_stack;
		img[x + y * w] = new_pixel;
		ret_cnt++;
		out.extend(vec2(x, y));

		int nx, ny;
		nx = x - 1;
		ny = y - 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			ret_cnt++;
			out.extend(vec2(nx, ny));
		}
		nx = x;
		ny = y - 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			ret_cnt++;
			out.extend(vec2(nx, ny));
		}
		nx = x + 1;
		ny = y - 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			ret_cnt++;
			out.extend(vec2(nx, ny));
		}
		nx = x - 1;
		ny = y;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			ret_cnt++;
			out.extend(vec2(nx, ny));
		}
		nx = x + 1;
		ny = y;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			ret_cnt++;
			out.extend(vec2(nx, ny));
		}
		nx = x - 1;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			ret_cnt++;
			out.extend(vec2(nx, ny));
		}
		nx = x;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			ret_cnt++;
			out.extend(vec2(nx, ny));
		}
		nx = x + 1;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			ret_cnt++;
			out.extend(vec2(nx, ny));
		}

		while (cal_stack.size()) {
			ivec2 elem = cal_stack.front();
			cal_stack.pop();
			x = elem[0];
			y = elem[1];

			img[x + y * w] = new_pixel;
			ret_cnt++;

			out.extend(vec2(x, y));

			nx = x - 1;
			ny = y - 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				ret_cnt++;
				out.extend(vec2(nx, ny));
			}
			nx = x;
			ny = y - 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				ret_cnt++;
				out.extend(vec2(nx, ny));
			}
			nx = x + 1;
			ny = y - 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				ret_cnt++;
				out.extend(vec2(nx, ny));
			}
			nx = x - 1;
			ny = y;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				ret_cnt++;
				out.extend(vec2(nx, ny));
			}
			nx = x + 1;
			ny = y;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				ret_cnt++;
				out.extend(vec2(nx, ny));
			}
			nx = x - 1;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				ret_cnt++;
				out.extend(vec2(nx, ny));
			}
			nx = x;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				ret_cnt++;
				out.extend(vec2(nx, ny));
			}
			nx = x + 1;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				ret_cnt++;
				out.extend(vec2(nx, ny));
			}
		}
		return ret_cnt;
	}
	template <typename T>
	void seed_fill_and_collect(int x, int y, int w, int h, T* img, T new_pixel, std::vector<ivec2>& region)
	{

		if (img[x + y * w] == new_pixel) return;

		T val = img[x + y * w];
		std::queue<ivec2> cal_stack;
		img[x + y * w] = new_pixel;
		region.push_back(ivec2(x, y));


		int nx, ny;
		nx = x - 1;
		ny = y - 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			region.push_back(ivec2(nx, ny));
		}
		nx = x;
		ny = y - 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			region.push_back(ivec2(nx, ny));
		}
		nx = x + 1;
		ny = y - 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			region.push_back(ivec2(nx, ny));
		}
		nx = x - 1;
		ny = y;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			region.push_back(ivec2(nx, ny));
		}
		nx = x + 1;
		ny = y;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			region.push_back(ivec2(nx, ny));
		}
		nx = x - 1;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			region.push_back(ivec2(nx, ny));
		}
		nx = x;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			region.push_back(ivec2(nx, ny));
		}
		nx = x + 1;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			region.push_back(ivec2(nx, ny));
		}

		while (cal_stack.size()) {
			ivec2 elem = cal_stack.front();
			cal_stack.pop();
			x = elem[0];
			y = elem[1];

			img[x + y * w] = new_pixel;
			//region.push_back(ivec2(x, y));

			nx = x - 1;
			ny = y - 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				region.push_back(ivec2(nx, ny));
			}
			nx = x;
			ny = y - 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				region.push_back(ivec2(nx, ny));
			}
			nx = x + 1;
			ny = y - 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				region.push_back(ivec2(nx, ny));
			}
			nx = x - 1;
			ny = y;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				region.push_back(ivec2(nx, ny));
			}
			nx = x + 1;
			ny = y;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				region.push_back(ivec2(nx, ny));
			}
			nx = x - 1;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				region.push_back(ivec2(nx, ny));
			}
			nx = x;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				region.push_back(ivec2(nx, ny));
			}
			nx = x + 1;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				region.push_back(ivec2(nx, ny));
			}
		}
	}
	template <typename T>
	void seed_fill_x(int x, int y, int w, int h, box2& roi, T* img, T new_pixel, T* reserve, T new_val, box2& out)
	{
		if (!roi.has_intersection(vec2(x, y))) return;
		if (img[x + y * w] == new_pixel) return;

		T val = img[x + y * w];
		std::queue<ivec2> cal_stack;
		img[x + y * w] = new_pixel;
		reserve[x + y * w] = new_val;

		out.extend(vec2(x, y));

		int nx, ny;

		nx = x;
		ny = y - 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}
		nx = x + 1;
		ny = y - 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}

		nx = x + 1;
		ny = y;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}

		nx = x;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}
		nx = x + 1;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}

		while (cal_stack.size()) {
			ivec2 elem = cal_stack.front();
			cal_stack.pop();
			x = elem[0];
			y = elem[1];

			img[x + y * w] = new_pixel;
			reserve[x + y * w] = new_val;

			out.extend(vec2(x, y));


			nx = x;
			ny = y - 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
			nx = x + 1;
			ny = y - 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}

			nx = x + 1;
			ny = y;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}

			nx = x;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
			nx = x + 1;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
		}
	}
	template <typename T>
	void seed_fill_x_and_collect(int x, int y, int w, int h, box2& roi, T* img, 
		T new_pixel, std::vector<ivec2>& crv, real tol)
	{
		if (!roi.has_intersection(vec2(x, y))) return;
		if (img[x + y * w] == new_pixel) return;

		T val = img[x + y * w];
		std::queue<ivec2> cal_stack;
		img[x + y * w] = new_pixel;
		crv.push_back(ivec2(x, y));

		int nx, ny;

		nx = x;
		ny = y - 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			crv.push_back(ivec2(nx, ny));
		}
		nx = x + 1;
		ny = y - 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			crv.push_back(ivec2(nx, ny));
		}

		nx = x + 1;
		ny = y;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			crv.push_back(ivec2(nx, ny));
		}

		nx = x;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			crv.push_back(ivec2(nx, ny));
		}
		nx = x + 1;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			crv.push_back(ivec2(nx, ny));
		}

		while (cal_stack.size()) {
			ivec2 elem = cal_stack.front();
			cal_stack.pop();
			x = elem[0];
			y = elem[1];
			vec2 v(crv[crv.size() - 1]);
			if (norm(vec2(x, y) - v) > tol) {
				return;
			}
			img[x + y * w] = new_pixel;

			crv.push_back(ivec2(x, y));
			nx = x;
			ny = y - 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				vec2 v(crv[crv.size() - 1]);
				if (norm(vec2(nx, ny) - v) > tol) {
					return;
				}
				img[nx + ny * w] = new_pixel;
				crv.push_back(ivec2(x, y));
			}
			nx = x + 1;
			ny = y - 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				vec2 v(crv[crv.size() - 1]);
				if (norm(vec2(nx, ny) - v) > tol) {
					return;
				}
				img[nx + ny * w] = new_pixel;
				crv.push_back(ivec2(x, y));
			}

			nx = x + 1;
			ny = y;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				vec2 v(crv[crv.size() - 1]);
				if (norm(vec2(nx, ny) - v) > tol) {
					return;
				}
				img[nx + ny * w] = new_pixel;
				crv.push_back(ivec2(x, y));
			}

			nx = x;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				vec2 v(crv[crv.size() - 1]);
				if (norm(vec2(nx, ny) - v) > tol) {
					return;
				}
				img[nx + ny * w] = new_pixel;
				crv.push_back(ivec2(x, y));
			}
			nx = x + 1;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				vec2 v(crv[crv.size() - 1]);
				if (norm(vec2(nx, ny) - v) > tol) {
					return;
				}
				img[nx + ny * w] = new_pixel;
				crv.push_back(ivec2(x, y));
			}
		}
	}
	template <typename T>
	void seed_fill_y(int x, int y, int w, int h, box2& roi, T* img, T new_pixel, T* reserve, T new_val, box2& out)
	{
		if (!roi.has_intersection(vec2(x, y))) return;
		if (img[x + y * w] == new_pixel) return;

		T val = img[x + y * w];
		std::queue<ivec2> cal_stack;
		img[x + y * w] = new_pixel;
		reserve[x + y * w] = new_val;

		out.extend(vec2(x, y));

		int nx, ny;
	
		nx = x - 1;
		ny = y;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}
		nx = x + 1;
		ny = y;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}
		nx = x - 1;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}
		nx = x;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}
		nx = x + 1;
		ny = y + 1;
		if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
			cal_stack.push(ivec2(nx, ny));
			img[nx + ny * w] = new_pixel;
			reserve[nx + ny * w] = new_val;
			out.extend(vec2(nx, ny));
		}

		while (cal_stack.size()) {
			ivec2 elem = cal_stack.front();
			cal_stack.pop();
			x = elem[0];
			y = elem[1];

			img[x + y * w] = new_pixel;
			reserve[x + y * w] = new_val;

			out.extend(vec2(x, y));

		
			nx = x - 1;
			ny = y;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
			nx = x + 1;
			ny = y;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
			nx = x - 1;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
			nx = x;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
			nx = x + 1;
			ny = y + 1;
			if (nx >= 0 && nx < w && ny >= 0 && ny < h && img[nx + ny * w] == val && roi.has_intersection(vec2(nx, ny))) {
				cal_stack.push(ivec2(nx, ny));
				img[nx + ny * w] = new_pixel;
				reserve[nx + ny * w] = new_val;
				out.extend(vec2(nx, ny));
			}
		}
	}
}
#endif