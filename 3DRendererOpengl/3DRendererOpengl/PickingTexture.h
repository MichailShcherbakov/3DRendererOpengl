#ifndef _PICKING_TEXTURE_H_
#define _PICKING_TEXTURE_H_

#include "GL/glew.h"

struct PixelInfo
{
	uint32_t ObjectID = 0;
	uint32_t DrawID = 0;
	uint32_t PrimID = 0;
};

class PickingTexture
{
public:
	void Initialize(size_t width, size_t height);
	void EnableWriting();
	void DisableWriting();
	PixelInfo ReadPixel(size_t x, size_t y);

private:
	GLuint m_framebuffer;
	GLuint m_pickingTexture;
	GLuint m_depthTexture;
};

#endif // _PICKING_TEXTURE_H_
