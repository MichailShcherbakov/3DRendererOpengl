#include "StdAfx.h"
#include "Object.h"

#include "GL/glew.h"
#include "glfw3.h"
#include "boost/filesystem.hpp"
#include "MaterialLibrary.h"

Object::Object()
{
}

Object::~Object()
{
	gParams->gRenderPipeline->RemoveListener(this);

	glDeleteVertexArrays((GLsizei)m_VAOs.size(), m_VAOs.data());
	m_VAOs.clear();
}

void Object::Draw(Shader& shader)
{
	shader.SetMat4("model", glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));
	shader.SetUInt("objectID", (unsigned int)this->objectID);

	for (size_t i = 0; i < m_VAOs.size(); ++i)
	{
		shader.SetUInt("drawID", (unsigned int)i);

		glBindVertexArray(m_VAOs[i]);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);

		if (m_pMaterialLibrary && m_pMaterialLibrary->IsLoaded())
		{
			auto material = m_pMaterialLibrary->GetMaterial(m_materialsName[i]);

			if (material)
			{
				shader.SetInt("diffuseMap", 0);
				shader.SetVec3("material.ambientColor", material->GetAmbient());
				shader.SetVec3("material.diffuseColor", material->GetDiffuse());
				shader.SetVec3("material.specularColor", material->GetSpecular());
				shader.SetFloat("material.shininess", material->GetSpecularExponent());

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, material->GetTexture()->GetHandle());
			}
			else
			{
				MSG(ETypeMessage::Error, "The Material was not found: " + m_materialsName[i]);
			}
		}

		glDrawArrays(GL_TRIANGLES, 0, m_numVertices[i]);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
	}
}

void Object::Initialize(const std::string&  path)
{
	gParams->gRenderPipeline->AddListener(this);

	if (!m_pLoader)
	{
		MSG(ETypeMessage::Error, "The Loader was not installed");
		return;
	}

	std::vector<Mesh*> meshes;

	m_pMaterialLibrary = new MaterialLibrary();
	m_pLoader->Load(path, meshes, m_pMaterialLibrary);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	for (const Mesh* mesh : meshes)
	{
		auto vertices = mesh->GetPolygonVertices();

		if (m_pMaterialLibrary && m_pMaterialLibrary->IsLoaded())
		{
			auto material = m_pMaterialLibrary->GetMaterial(mesh->GetMaterialName());

			if (material)
			{
				m_materialsName.push_back(material->GetTitle());
			}
			else
			{
				MSG(ETypeMessage::Error, "The Material was not found: " + mesh->GetMaterialName());
			}
		}

		for (int i = 0; i < vertices.size(); ++i)
		{
			if (i == 0)
			{
				minX = maxX = vertices[i].position.x;
				minY = maxY = vertices[i].position.y;
				minZ = maxZ = vertices[i].position.z;
			}

			minX = std::fminf(minX, vertices[i].position.x);
			maxX = std::fmaxf(maxX, vertices[i].position.x);

			minY = std::fminf(minY, vertices[i].position.y);
			maxY = std::fmaxf(maxY, vertices[i].position.y);

			minZ = std::fminf(minZ, vertices[i].position.z);
			maxZ = std::fmaxf(maxZ, vertices[i].position.z);
		}

		GLuint VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(sizeof(glm::vec3)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(sizeof(glm::vec3) * 2));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(sizeof(glm::vec3) * 2 + sizeof(glm::vec2)));
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(sizeof(glm::vec3) * 3 + sizeof(glm::vec2)));

		m_numVertices.push_back((GLsizei)vertices.size());
		m_VAOs.push_back(VAO);
		
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);

	if (meshes.size() > 0 && m_pBoundingBox)
	{
		m_pBoundingBox->Process(minX, maxX, minY, maxY, minZ, maxZ);
	}
}

void Object::SetLoader(ILoader* loader)
{
	m_pLoader = loader;
}

void Object::SetBoundingBox(BoundingBox* boundingBox)
{
	m_pBoundingBox = boundingBox;
	m_pBoundingBox->Process(minX, maxX, minY, maxY, minZ, maxZ);
}
