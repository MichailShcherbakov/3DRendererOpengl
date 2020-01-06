#include "StdAfx.h"
#include "Texture2D.h"

#include "GL/glew.h"
#include <sstream>

Texture2D::Texture2D()
{
}

Texture2D::Texture2D(const std::string& path, bool mirrored)
{
	Load(path, mirrored);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_handle);
	m_handle = 0;
}

void Texture2D::Load(const std::string& path, bool mirrored)
{
	m_isLoaded = false;

	GLuint textureID;
	glGenTextures(1, &textureID);

	if (mirrored)
		stbi_set_flip_vertically_on_load(true);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 2)
			format = GL_RG;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}
	else
	{
		MSG(ETypeMessage::Error, "The texture failed to load at path: " + path);
		stbi_image_free(data);
		if (mirrored)
			stbi_set_flip_vertically_on_load(true);
	}

	if (mirrored)
		stbi_set_flip_vertically_on_load(false);

	m_handle = textureID;
	m_isLoaded = true;
}

bool Texture2D::IsLoaded() const
{
	return m_isLoaded;
}

bool Texture2D::IsLoaded()
{
	return m_isLoaded;
}

GLuint Texture2D::GetHandle() const
{
	return m_handle;
}

GLuint Texture2D::GetHandle()
{
	return m_handle;
}
