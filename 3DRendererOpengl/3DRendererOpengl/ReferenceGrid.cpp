#include "StdAfx.h"
#include "ReferenceGrid.h"

ReferenceGrid::ReferenceGrid(float width, float length)
{
	m_width = width;
	m_length = length;
}

ReferenceGrid::~ReferenceGrid()
{
	//gParams->gRenderPipeline->RemoveListener(this);
}

void ReferenceGrid::Draw(Shader& shader)
{
	auto width = m_width / 2;
	auto length = m_length / 2;

	shader.SetMat4("model", glm::mat4(1.0f));
	shader.SetVec4("lineColor", glm::vec4(1.0f));

	GLfloat vertices[] = {
		// position					// texCoord
		-width, 0.0f, -length,		0.0f, 1.0f,
		-width, 0.0f, length,		0.0f, 0.0f,
		width, 0.0f, length,		1.0f, 0.0f,
		width, 0.0f, -length,		1.0f, 1.0f,
	};

	GLushort indices[] = {
		0, 1, 2, 2, 3, 0
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (const void*)(sizeof(GLfloat) * 3));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ReferenceGrid::Initialize()
{
	//gParams->gRenderPipeline->AddListener(this);
}
