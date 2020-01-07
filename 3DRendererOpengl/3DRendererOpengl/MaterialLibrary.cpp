#include "StdAfx.h"
#include "MaterialLibrary.h"

#include <vector>
#include <fstream>
#include <algorithm>
#include <boost/filesystem.hpp>

MaterialLibrary::MaterialLibrary()
{
}

MaterialLibrary::MaterialLibrary(const std::string& path)
{
	Load(path);
}

MaterialLibrary::~MaterialLibrary()
{
	Clear();
}

void MaterialLibrary::Load(const std::string& path)
{
	m_isLoaded = false;

	if (!m_materials.empty() || !m_textures.empty())
		Clear();

	std::ifstream file;
	file.open(path);

	if (!file.is_open())
	{
		MSG(ETypeMessage::Error, "The Material library file was not opened: " + path);
		return;
	}

	MSG(ETypeMessage::Log, "The Material library file was successfully opened");

	Material* material = nullptr;

	while (!file.eof())
	{
		std::string strLine;
		file >> strLine;
		const char* str = strLine.c_str();

		if (strcmp(str, "newmtl") == 0)
		{
			material = nullptr;

			std::string title;
			file.ignore(1);
			std::getline(file, title);

			auto fmaterial = std::find_if(m_materials.begin(), m_materials.end(), [=](const Material* material) { return material->GetTitle() == title; });

			if (fmaterial != m_materials.end())
				continue;

			material = new Material(title);

			m_materials.push_back(material);
		}
		else if (strcmp(str, "Ka") == 0 && material)
		{
			glm::vec3 ambient;
			file >> ambient.x;
			file >> ambient.y;
			file >> ambient.z;

			material->SetAmbient(ambient);
		}
		else if (strcmp(str, "Kd") == 0 && material)
		{
			glm::vec3 diffuse;
			file >> diffuse.x;
			file >> diffuse.y;
			file >> diffuse.z;

			material->SetDiffuse(diffuse);
		}
		else if (strcmp(str, "Ks") == 0 && material)
		{
			glm::vec3 specular;
			file >> specular.x;
			file >> specular.y;
			file >> specular.z;

			material->SetSpecular(specular);
		}
		else if (strcmp(str, "Ns") == 0 && material)
		{
			float specularExponent;
			file >> specularExponent;
			material->SetSpecularExponent(specularExponent);
		}
		else if (strcmp(str, "map_Kd") == 0 && material)
		{
			std::string diffuseMap;
			file.ignore(1);
			std::getline(file, diffuseMap);

			Texture2D* texture = new Texture2D();
			texture->Load(boost::filesystem::absolute("Textures/" + diffuseMap).string(), true);

			if (!texture->IsLoaded())
				delete texture;
			else
			{
				m_textures.push_back(texture);
				material->SetTexture(texture);
			}	
		}
	}

	file.close();

	MSG(ETypeMessage::Log, "The Material library file was successfully loaded");

	m_isLoaded = true;
}

bool MaterialLibrary::IsLoaded() const
{
	return m_isLoaded;
}

bool MaterialLibrary::IsEmpty() const
{
	return m_materials.empty();
}

const Material* MaterialLibrary::GetMaterial(const std::string& title)
{
	auto material = std::find_if(m_materials.begin(), m_materials.end(), [=](const Material* material) { return material->GetTitle() == title; });

	if (material != m_materials.end())
		return *material;

	return nullptr;
}

void MaterialLibrary::SetMaterial(const Material* material)
{
	if (std::find(m_textures.begin(), m_textures.end(), material->GetTexture()) == m_textures.end())
		m_textures.push_back(material->GetTexture());

	if (std::find(m_materials.begin(), m_materials.end(), material) == m_materials.end())
		m_materials.push_back(material);
}

void MaterialLibrary::Clear()
{
	for (auto material : m_materials)
		delete material;

	for (auto texture : m_textures)
		delete texture;

	m_materials.clear();
	m_textures.clear();
}
