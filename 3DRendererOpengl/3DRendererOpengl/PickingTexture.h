#ifndef _PICKING_TEXTURE_H_
#define _PICKING_TEXTURE_H_

#include "GL/glew.h"

struct PixelInfo
{
	unsigned int ObjectID = 0;
	unsigned int DrawID = 0;
	unsigned int PrimID = 0;
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
