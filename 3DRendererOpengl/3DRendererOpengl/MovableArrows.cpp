#include "StdAfx.h"
#include "MovableArrows.h"

MovableArrows::MovableArrows()
{
}

void MovableArrows::Draw(Shader& shader)
{
	auto t = this->objectID;
	shader.SetMat4("model", glm::mat4(1.0f));
	shader.SetUInt("objectIndex", (unsigned int)this->objectID);
	shader.SetUInt("drawIndex", 0);

	glm::vec3 targetPosition(0.0f);
	glm::vec3 m_position(0.0f);
	float length = 0.5f;
	float R = 0.2f;

	GLfloat vertices[] = {
		// position														// color
		m_position.x, targetPosition.y, targetPosition.z,				1.0f, 0.0f, 0.0f,
		m_position.x + length, targetPosition.y, targetPosition.z,		1.0f, 0.0f, 0.0f,

		targetPosition.y, m_position.y, targetPosition.z,				0.0f, 1.0f, 0.0f,
		targetPosition.y, m_position.y - length, targetPosition.z,		0.0f, 1.0f, 0.0f,

		targetPosition.x, targetPosition.y, m_position.z,				0.0f, 0.0f, 1.0f,
		targetPosition.x, targetPosition.y, m_position.z - length,		0.0f, 0.0f, 1.0f,
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (const void*)(sizeof(GLfloat) * 3));

	glDrawArrays(GL_LINES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDeleteBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	RenderArrows();
}

void MovableArrows::Initialize()
{
}

void MovableArrows::RenderArrows()
{
	glm::vec3 targetPosition(0.0f);
	glm::vec3 m_position(0.0f);
	float length = 0.5f;
	float R = 0.01f;

	GLfloat vertices[] = {
		// position																	// color
		m_position.x + length + R * 4, targetPosition.y, targetPosition.z,				1.0f, 0.0f, 0.0f,
		m_position.x + length, targetPosition.y + R, targetPosition.z + R,			1.0f, 0.0f, 0.0f,
		m_position.x + length, targetPosition.y - R, targetPosition.z + R,			1.0f, 0.0f, 0.0f,
		m_position.x + length, targetPosition.y - R, targetPosition.z - R,			1.0f, 0.0f, 0.0f,
		m_position.x + length, targetPosition.y + R, targetPosition.z - R,			1.0f, 0.0f, 0.0f,
	};

	GLushort indices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 1,
		1, 2, 3,
		3, 4, 1
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (const void*)(sizeof(GLfloat) * 3));

	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
