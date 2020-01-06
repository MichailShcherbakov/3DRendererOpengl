#include "StdAfx.h"
#include "Billboard.h"

Billboard::~Billboard()
{
	gParams->gRenderPipeline->RemoveListener(this);
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void Billboard::Draw(Shader& shader)
{
	shader.SetInt("diffuseMap", 0);
	shader.SetVec2("size", m_size);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetHandle());
	
	glBindVertexArray(m_VAO);

	glEnableVertexAttribArray(0);

	glDrawArrays(GL_POINTS, 0, 1);

	glDisableVertexAttribArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Billboard::MousePressEvent(MouseEvent* event)
{
}

void Billboard::MouseReleaseEvent(MouseEvent* event)
{
}

void Billboard::MouseMoveEvent(MouseEvent* event)
{
}

void Billboard::KeyPressEvent(KeyEvent* event)
{
}

void Billboard::KeyReleaseEvent(KeyEvent* event)
{
}

void Billboard::Initialize()
{
	gParams->gRenderPipeline->AddListener(this);

	Process();
}

void Billboard::Process()
{
	if (m_VAO != 0 && m_VBO != 0)
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_position), &m_position, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const void*)0);

	glDisableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_VAO = VAO;
	m_VBO = VBO;
}

void Billboard::SetPosition(const glm::vec3& position)
{
	m_position = position;
	Process();
}

void Billboard::SetSize(float_t width, float_t height)
{
	m_size = glm::vec2(width, height);
}

void Billboard::SetTexture(const Texture2D& texture)
{
	m_texture = texture;
}
