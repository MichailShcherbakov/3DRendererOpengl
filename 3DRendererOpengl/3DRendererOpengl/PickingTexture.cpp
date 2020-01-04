#include "StdAfx.h"
#include "PickingTexture.h"

void PickingTexture::Initialize(size_t width, size_t height)
{
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	glGenTextures(1, &m_pickingTexture);
	glBindTexture(GL_TEXTURE_2D, m_pickingTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32UI, (GLsizei)width, (GLsizei)height, 0, GL_RGB_INTEGER, GL_UNSIGNED_INT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pickingTexture, 0);

	glGenTextures(1, &m_depthTexture);
	glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, (GLsizei)width, (GLsizei)height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE) {

		MSG(ETypeMessage::Error, "The picking texture was not successfully initialize")

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PickingTexture::EnableWriting()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PickingTexture::DisableWriting()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

PixelInfo PickingTexture::ReadPixel(size_t x, size_t y)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	glReadBuffer(GL_COLOR_ATTACHMENT0);

	PixelInfo pixelInfo;
	glReadPixels((GLuint)x, (GLuint)y, 1, 1, GL_RGB_INTEGER, GL_UNSIGNED_INT, &pixelInfo);

	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return pixelInfo;
}
