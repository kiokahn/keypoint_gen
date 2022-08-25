#pragma once


namespace graphics {

	// open image file fname and write the content to alloc,
	// im is allocated inside the load_image function
	// output is RGBA8 format
	// return true if file exist
	bool load_image(const wchar_t* fname, int& w, int& h, unsigned char*& im);

	// open image file fname and write the content to alloc,
	// im is allocated inside the load_image function
	// output is RGBA8 format
	// image is resized to w/h image size
	// return true if file exist
	bool load_image(const wchar_t* fname, int & w, int& h, int sw, int sh, unsigned char*& im);

	void save_image(const wchar_t* fname, int w, int h, unsigned char* im);
	bool load_texture(const wchar_t* fname, unsigned int& ogl_texture);
	bool load_texture(const wchar_t* fname, int & w, int& h, unsigned int& ogl_texture);
}