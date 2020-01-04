#include "StdAfx.h"
#include "CubeTexture.h"

#include "GL/glew.h"
#include "stb/stb_image.h"

CubeTexture::CubeTexture()
{
}

CubeTexture::CubeTexture(const std::vector<std::string>& texturesPaths, bool mirrored)
{
	Load(texturesPaths, mirrored);
}

CubeTexture::~CubeTexture()
{
	glDeleteTextures(1, &m_handle);
	m_handle = 0;
}

void CubeTexture::Load(const std::vector<std::string>& texturesPaths, bool mirrored)
{
	m_isLoaded = false;

	if (texturesPaths.size() != 6)
	{
		MSG(ETypeMessage::Error, "The number of texture2D must be six: " + std::to_string(texturesPaths.size()))
		return;
	}

	if (mirrored)
		stbi_set_flip_vertically_on_load(true);

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int width, height, nrChannels;
	for (int32_t i = 0; i < texturesPaths.size(); ++i)
	{
		unsigned char* data = stbi_load(texturesPaths[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			MSG(ETypeMessage::Error, "The cube map texture failed to load at path: " + texturesPaths[i])
			stbi_image_free(data);

			if (mirrored)
				stbi_set_flip_vertically_on_load(false);

			return;
		}
	}
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	MSG(ETypeMessage::Log, "The cube map texture was successfully loaded");
	m_isLoaded = true;
	m_handle = texture;

	if (mirrored)
		stbi_set_flip_vertically_on_load(false);
}

bool CubeTexture::IsLoaded() const
{
	return m_isLoaded;
}

bool CubeTexture::IsLoaded()
{
	return m_isLoaded;
}

GLuint CubeTexture::GetHandle() const
{
	return m_handle;
}

GLuint CubeTexture::GetHandle()
{
	return m_handle;
}
