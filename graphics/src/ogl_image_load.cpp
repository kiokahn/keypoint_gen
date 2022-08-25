#include <graphics/ogl_image_load.h>
#include <QtGui/QImage>
#include <graphics/gl.h>
namespace graphics
{
bool load_image(const wchar_t* fname, int& w, int& h, unsigned char*& im)
{
	QImage loaded;
	if (loaded.load(QString::fromStdWString(fname)))
	{
		w = loaded.width();
		h = loaded.height();
		im = (unsigned char*)malloc(w*h * 4);
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				QRgb v = loaded.pixel(x, h-y-1);
				im[x * 4 + y * w * 4] = qRed(v);
				im[x * 4 + y * w * 4 + 1] = qGreen(v);
				im[x * 4 + y * w * 4 + 2] = qBlue(v);
				im[x * 4 + y * w * 4 + 3] = qAlpha(v);
			}
		}
		return true;
	}
	return false;
}

bool load_image(const wchar_t* fname, int& w, int& h, int sw, int sh, unsigned char*& im)
{
	QImage loaded;
	if (loaded.load(QString::fromStdWString(fname)))
	{
		w = loaded.width();
		h = loaded.height();

		QImage resized = loaded.scaled(sw, sh);

		im = (unsigned char*)malloc(sw*sh * 4);
		for (int x = 0; x < sw; x++) {
			for (int y = 0; y < sh; y++) {
				QRgb v = resized.pixel(x, sh - y - 1);
				im[x * 4 + y * sw * 4] = qRed(v);
				im[x * 4 + y * sw * 4 + 1] = qGreen(v);
				im[x * 4 + y * sw * 4 + 2] = qBlue(v);
				im[x * 4 + y * sw * 4 + 3] = qAlpha(v);
			}
		}
		return true;
	}
	return false;
}

void save_image(const wchar_t* fname, int w, int h, unsigned char* im)
{
	QImage save(w, h,QImage::Format::Format_RGBA8888);


	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			QRgb v = qRgba(im[x * 4 + y * w * 4], im[x * 4 + y * w * 4 + 1], im[x * 4 + y * w * 4 + 2], im[x * 4 + y * w * 4 + 3]);
			save.save(QString::fromStdWString(fname));
		}
	}
}
bool load_texture(const wchar_t* fname, unsigned int& ogl_texture)
{
	int w, h;
	unsigned char* im;
	bool suc = load_image(fname, w, h, im);
	if (!suc) return suc;
	{
		glGenTextures(1, &ogl_texture);
		glBindTexture(GL_TEXTURE_2D, ogl_texture);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, im);
		//glTexImage2D( GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData() );
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	free(im);
	return suc;

}

bool load_texture(const wchar_t* fname,  int& w, int &h, unsigned int& ogl_texture)
{

	unsigned char* im;
	bool suc = load_image(fname, w, h, im);
	if (!suc) return suc;
	{
		glGenTextures(1, &ogl_texture);
		glBindTexture(GL_TEXTURE_2D, ogl_texture);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, im);
		//glTexImage2D( GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData() );
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	free(im);
	return suc;

}
}