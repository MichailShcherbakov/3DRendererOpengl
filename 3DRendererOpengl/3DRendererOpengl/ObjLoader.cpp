#include "StdAfx.h"
#include "ObjLoader.h"

#include "MaterialLibrary.h"
#include <string>
#include <fstream>
#include "boost/filesystem.hpp"

void ObjLoader::Load(const std::string& path, std::vector<Mesh*>& meshes, IMaterialLibrary* library)
{
	std::ifstream file;
	file.open(path);
	
	if (!file.is_open())
	{
		MSG(ETypeMessage::Error, "The vertices file was not opened: " + path);
		return;
	}

	MSG(ETypeMessage::Log, "The vertices file was successfully opened");

	ObjMesh* objMesh = nullptr;

	while (!file.eof())
	{
		std::string strline;
		file >> strline;
		const char* str = strline.c_str();

		if (strcmp(str, "o") == 0)
		{
			if (objMesh)
			{
				Mesh* mesh = new Mesh();

				for (const Index& index : objMesh->indices)
				{
					Vertex vertex;

					if (index.vertex > 0)
						vertex.position = objMesh->vertices[index.vertex - 1];

					if (index.normal > 0)
						vertex.normal = objMesh->normals[index.normal - 1];

					if (index.uv > 0)
						vertex.texCoord = objMesh->texCoords[index.uv - 1];

					mesh->AddVertex(vertex);
				}

				if (objMesh->materialName != "")
					mesh->SetMaterialName(objMesh->materialName);

				meshes.push_back(mesh);
			}

			objMesh = new ObjMesh();
		}
		else if (strcmp(str, "v") == 0 && objMesh)
		{
			glm::vec3 vertex;
			file >> vertex.x;
			file >> vertex.y;
			file >> vertex.z;

			vertex *= -1; /* inverse */

			objMesh->vertices.push_back(vertex);
		}
		else if (strcmp(str, "vn") == 0 && objMesh)
		{
			glm::vec3 normal;
			file >> normal.x;
			file >> normal.y;
			file >> normal.z;

			objMesh->normals.push_back(normal);
		}
		else if (strcmp(str, "vt") == 0 && objMesh)
		{
			glm::vec2 texCoord;
			file >> texCoord.x;
			file >> texCoord.y;

			objMesh->texCoords.push_back(texCoord);
		}
		else if (strcmp(str, "f") == 0 && objMesh)
		{
			Index index, index2, index3;

			std::string t;
			file >> t;

			if (std::count(t.begin(), t.end(), '/') == 1)
			{
				index.vertex = std::stoi( t.substr(0, t.find('/')));
				index.uv = std::stoi( t.substr(t.find('/')+1, t.size()));

				file >> index2.vertex;
				file.ignore(1);
				file >> index2.uv;

				file >> index3.vertex;
				file.ignore(1);
				file >> index3.uv;
			}
			else if (t.find("//") < t.size())
			{
				index.vertex = std::stoi(t.substr(0, t.find('/')));
				index.normal = std::stoi(t.substr(t.find('/') + 2, t.size()));

				file >> index2.vertex;
				file.ignore(1);
				file >> index2.normal;

				file >> index3.vertex;
				file.ignore(1);
				file >> index3.normal;
			}
			else if (std::count(t.begin(), t.end(), '/') == 2)
			{
				index.vertex = std::stoi(t.substr(0, t.find('/')));
				index.uv = std::stoi(t.substr(t.find('/') + 1, t.rfind('/')));
				index.normal = std::stoi(t.substr(t.rfind('/') + 1, t.size()));

				file >> index2.vertex;
				file.ignore(1);
				file >> index2.uv;
				file.ignore(1);
				file >> index2.normal;

				file >> index3.vertex;
				file.ignore(1);
				file >> index3.uv;
				file.ignore(1);
				file >> index3.normal;
			}
			else
			{
				index.vertex = std::stoi(t);
				file >> index2.vertex;
				file >> index3.vertex;
			}

			objMesh->indices.push_back(index);
			objMesh->indices.push_back(index2);
			objMesh->indices.push_back(index3);
		}
		else if (strcmp(str, "mtllib") == 0)
		{
			std::string title;
			file.ignore(1);
			std::getline(file, title);

			*library = MaterialLibrary();
			library->Load(boost::filesystem::absolute("Materials/" + title).string());

			if (!library->IsLoaded())
			{
				delete library;
				library = nullptr;
			}
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			std::string title;
			file.ignore(1);
			std::getline(file, title);

			objMesh->materialName = title;
		}
	}

	Mesh* mesh = new Mesh();

	for (const Index& index : objMesh->indices)
	{
		Vertex vertex;

		if (index.vertex > 0)
			vertex.position = objMesh->vertices[index.vertex - 1];

		if (index.normal > 0)
			vertex.normal = objMesh->normals[index.normal - 1];

		if (index.uv > 0)
			vertex.texCoord = objMesh->texCoords[index.uv - 1];

		mesh->AddVertex(vertex);
	}

	if (objMesh->materialName != "")
		mesh->SetMaterialName(objMesh->materialName);

	meshes.push_back(mesh);

	file.close();

	MSG(ETypeMessage::Log, "The vertices file was successfully loaded");
}
