#include "StdAfx.h"
#include "Skybox.h"

#include "Mesh.h"

Skybox::Skybox()
{
}

Skybox::Skybox(float size, const CubeTexture& diffuseMap)
{
	Initialize(size, diffuseMap);
}

Skybox::~Skybox()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

void Skybox::Draw(Shader& shader)
{
	shader.SetInt("diffuseMap", 0);

	glDepthFunc(GL_LEQUAL);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_diffuseMap.GetHandle());

	glBindVertexArray(m_VAO);

	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
}

void Skybox::MousePressEvent(MouseEvent* event)
{
}

void Skybox::MouseReleaseEvent(MouseEvent* event)
{
}

void Skybox::MouseMoveEvent(MouseEvent* event)
{
}

void Skybox::KeyPressEvent(KeyEvent* event)
{
}

void Skybox::KeyReleaseEvent(KeyEvent* event)
{
}

void Skybox::Initialize(float size, const CubeTexture& diffuseMap)
{
	m_diffuseMap = diffuseMap;

	size = size / 2.0f;

	GLfloat vertices[] = {
		-size,  size, -size,
		-size, -size, -size,
		size, -size, -size,
		 size, -size, -size,
		 size,  size, -size,
		-size,  size, -size,

		-size, -size,  size,
		-size, -size, -size,
		-size,  size, -size,
		-size,  size, -size,
		-size,  size,  size,
		-size, -size,  size,

		 size, -size, -size,
		 size, -size,  size,
		 size,  size,  size,
		 size,  size,  size,
		 size,  size, -size,
		 size, -size, -size,

		-size, -size,  size,
		-size,  size,  size,
		 size,  size,  size,
		 size,  size,  size,
		 size, -size,  size,
		-size, -size,  size,

		-size,  size, -size,
		 size,  size, -size,
		 size,  size,  size,
		 size,  size,  size,
		-size,  size,  size,
		-size,  size, -size,

		-size, -size, -size,
		-size, -size,  size,
		 size, -size, -size,
		 size, -size, -size,
		-size, -size,  size,
		 size, -size,  size
	};

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const void*)0);

	glDisableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_VAO = VAO;
	m_VBO = VBO;
}

CubeTexture Skybox::GetTexture() const
{
	return m_diffuseMap;
}
