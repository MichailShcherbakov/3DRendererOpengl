#ifndef _MESH_H_
#define _MESH_H_

#include "glm/glm.hpp"

#include <vector>
#include <string>

struct Index
{
	unsigned int vertex = 0;
	unsigned int uv = 0;
	unsigned int normal = 0;
};

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

class Mesh
{
public:
	void AddVertex(const Vertex& vertex);
	void SetPolygonVertices(const std::vector<Vertex>& vertices);
	std::vector<Vertex> GetPolygonVertices(); 
	std::vector<Vertex> GetPolygonVertices() const; 
	std::string GetMaterialName(); 
	std::string GetMaterialName() const;
	void SetMaterialName(const std::string& title);

private:
	std::vector<Vertex> m_vertices;
	std::string m_materialName;
};

#endif // _MESH_H_