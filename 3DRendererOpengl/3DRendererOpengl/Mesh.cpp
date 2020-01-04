#include "StdAfx.h"
#include "Mesh.h"

void Mesh::AddVertex(const Vertex& vertex)
{
	m_vertices.push_back(vertex);
}

void Mesh::SetPolygonVertices(const std::vector<Vertex>& vertices)
{
	m_vertices = vertices;
}

std::vector<Vertex> Mesh::GetPolygonVertices()
{
	return m_vertices;
}

std::vector<Vertex> Mesh::GetPolygonVertices() const
{
	return m_vertices;
}

std::string Mesh::GetMaterialName()
{
	return m_materialName;
}

std::string Mesh::GetMaterialName() const
{
	return m_materialName;
}

void Mesh::SetMaterialName(const std::string& title)
{
	m_materialName = title;
}
