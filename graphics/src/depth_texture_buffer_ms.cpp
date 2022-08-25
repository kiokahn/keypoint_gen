#include	"graphics/depth_texture_buffer_ms.h"

namespace graphics {

DepthTextureBufferMS::DepthTextureBufferMS()
	: DepthTextureBuffer(), tmp_fbo_(0), tmp_tx_(0)
{
}


DepthTextureBufferMS::~DepthTextureBufferMS()
{
	delete_temp_fbo(tmp_fbo_, tmp_tx_);

}

void 
DepthTextureBufferMS::GenerateObjects(uint mag_filter, uint min_filter)
{
	glGenTextures(1, &texture_id_);

	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture_id_);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, width_, height_, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);


	glGenTextures(1, &depth_texture_id_);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, depth_texture_id_);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_DEPTH_COMPONENT24, width_, height_, GL_TRUE);

	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	glGenFramebuffers(1, &fbo_id_);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_id_);
	

	// attach the texture to FBO color attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
		GL_TEXTURE_2D_MULTISAMPLE, texture_id_, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT,
		GL_TEXTURE_2D_MULTISAMPLE, depth_texture_id_, 0);
	/*glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
							  texture_id_, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
							  depth_texture_id_, 0);*/


	//std::vector<GLenum> drawbuffer;
	//drawbuffer.push_back(GL_COLOR_ATTACHMENT0);
	//glDrawBuffers(drawbuffer.size(), &drawbuffer[0]);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DepthTextureBufferMS::make_temp_fbo(uint& fbo, uint& tx)
{
	if (fbo && tx) return;
	glGenTextures(1, &tx);

	glBindTexture(GL_TEXTURE_2D, tx);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);


	glGenFramebuffersEXT(1, &fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);

	// attach the texture to FBO color attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
		GL_TEXTURE_2D, tx, 0);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
}

void DepthTextureBufferMS::delete_temp_fbo(uint& fbo, uint& tx)
{
	if (!fbo)
		glDeleteFramebuffersEXT(1, &fbo);


	if (!tx)
		glDeleteTextures(1, &tx);

	fbo = 0;
	tx = 0;
}


void DepthTextureBufferMS::ReadData(void* ptr)
{

	make_temp_fbo(tmp_fbo_, tmp_tx_);

	if (!pbo_id_) glGenBuffersARB(1, &pbo_id_);

	glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, fbo_id_);
	glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, tmp_fbo_);
	glBlitFramebufferEXT(0, 0, width_, height_, 0, 0, width_, height_, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, 0);
	glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, tmp_fbo_);
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pbo_id_);


	glBufferDataARB(GL_PIXEL_PACK_BUFFER_ARB, width_* height_ * 4, 0, GL_STREAM_READ_ARB);
	glReadPixels(0, 0, width_, height_, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	GLubyte* src = (GLubyte*)glMapBufferARB(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY_ARB);
	if (src)
	{
		memcpy(ptr, src, width_* height_ * 4);
		glUnmapBufferARB(GL_PIXEL_PACK_BUFFER_ARB); // release the mapped buffer
	}

	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void
DepthTextureBufferMS::Resize(int w, int h)
{
	if (width_ == w && height_ == h) return;

	width_ = w; height_ = h;

	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture_id_);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, width_, height_, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, depth_texture_id_);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_DEPTH_COMPONENT24, width_, height_, GL_TRUE);

	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	delete_temp_fbo(tmp_fbo_, tmp_tx_);
}


};