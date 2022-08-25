#ifndef __depth_texture_buffer_ms_h
#define __depth_texture_buffer_ms_h

#include "graphics/sys.h"
#include "graphics/gl.h"
#include "graphics/gl_extension.h"
#include "graphics/unsigned.h"
#include "graphics/depth_texture_buffer.h"

namespace graphics {

class DepthTextureBufferMS : public DepthTextureBuffer{
	uint tmp_fbo_, tmp_tx_;
public:

	DepthTextureBufferMS();
	virtual ~DepthTextureBufferMS();

	virtual void GenerateObjects(uint mag_filter = GL_NEAREST, uint min_filter = GL_NEAREST);
	virtual void Resize(int w, int h);


	virtual void ReadData(void* ptr);


protected:

	void make_temp_fbo(uint& fbo, uint& tx);
	void delete_temp_fbo(uint& fbo, uint& tx);
};

};

#endif