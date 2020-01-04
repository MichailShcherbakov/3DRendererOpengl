#include "StdAfx.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	Process(minX, maxX, minY, maxY, minZ, maxZ);
}

void BoundingBox::Process(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	m_size = glm::vec3(maxX - minX, maxY - minY, maxZ - minZ);
	m_center = glm::vec3((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2);
	m_transform = glm::translate(glm::mat4(1.0f), 0.5f * m_center) * glm::scale(glm::mat4(1.0f), 0.5f * m_size);
}

void BoundingBox::Draw(Shader& shader)
{
	shader.SetMat4("model", m_transform);

	GLfloat vertices[] = {
		// position					// color
		-0.5f, -0.5f, 0.5f,			1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,			1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f,			1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f,			1.0f, 1.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,			1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f,			1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,			1.0f, 1.0f, 1.0f,
	};

	GLushort indices[] = {
		0, 1,
		1, 2,
		2, 3,
		3, 0,
		
		4, 5,
		5, 6,
		6, 7,
		7, 4,
		
		0, 4,
		1, 5,
		2, 6,
		3, 7,

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

	glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
