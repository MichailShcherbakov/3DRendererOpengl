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

Texture2D::Texture2D(const void* data, GLuint width, GLuint height)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	m_isLoaded = true;
	m_handle = texture;
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D()
{
	if (m_isLoaded)
		Clear();
}

void Texture2D::Load(const std::string& path, bool mirrored)
{
	if (m_isLoaded)
		Clear();

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
		if (nrComponents == 4)
			format = GL_RGBA;
		else
			format = GL_RGB;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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
GLuint Texture2D::GetHandle() const
{
	return m_handle;
}

void Texture2D::Clear()
{
	glDeleteTextures(1, &m_handle);
	m_handle = 0;
}