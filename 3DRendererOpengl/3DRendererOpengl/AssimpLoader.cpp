#include "StdAfx.h"
#include "AssimpLoader.h"

void AssimpLoader::Load(const std::string& path, std::vector<Mesh*>& meshes, IMaterialLibrary* library)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, 
		aiProcess_Triangulate | 
		aiProcess_FlipUVs | 
		aiProcess_CalcTangentSpace | 
		aiProcess_GenNormals | 
		aiProcess_GenUVCoords);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LogError(importer.GetErrorString());
		return;
	}

	Log("The vertices file was successfully opened");

	ProcessNode(scene->mRootNode, scene);

	meshes = m_meshes;
	m_meshes.clear();

	if (m_materialLibrary)
	{
		Log("The material library was successfully loaded");
		*library = *m_materialLibrary;
	}

	m_materialLibrary = nullptr;

	Log("The vertices file was successfully loaded");
}

void AssimpLoader::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (uint32_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (uint32_t i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh* AssimpLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	Mesh* meshPol = new Mesh();

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<Texture2D> textures;

	for (uint32_t i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector; 
		
		if (mesh->mVertices != nullptr)
		{
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;
		}

		if (mesh->mNormals != nullptr)
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoord = vec;
		}
		else
			vertex.texCoord = glm::vec2(0.0f, 0.0f);

		if (mesh->mTangents != nullptr)
		{
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.tangent = vector;
		}

		if (mesh->mBitangents != nullptr)
		{
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.bitangent = vector;
		}

		vertices.push_back(vertex);
	}
	
	for (uint32_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (uint32_t j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	meshPol->SetIndices(indices);

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	meshPol->SetMaterialName(material->GetName().C_Str());

	std::vector<Texture2D> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	/*std::vector<Texture2D> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	std::vector<Texture2D> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT);
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	std::vector<Texture2D> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT);
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());*/

	meshPol->SetPolygonVertices(vertices);

	return meshPol;
}

std::vector<Texture2D> AssimpLoader::loadMaterialTextures(aiMaterial* mat, aiTextureType type)
{
	std::vector<Texture2D> textures;

	Material* material = new Material(mat->GetName().C_Str());

	for (uint32_t i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		std::string path = "Textures/";
		path += str.C_Str();

		material->SetTexture(new Texture2D(path));
	}

	if (!material->GetTexture())
	{
		GLubyte color[] = { 200, 200, 200 };
		material->SetTexture(new Texture2D(color, 1, 1));
	}
	
	aiColor3D diffuse(1.f, 1.f, 1.f);
	mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	material->SetDiffuse(glm::vec3(diffuse.r, diffuse.g, diffuse.b));

	aiColor3D ambient(1.f, 1.f, 1.f);
	mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
	material->SetAmbient(glm::vec3(ambient.r, ambient.g, ambient.b));

	aiColor3D specular(1.f, 1.f, 1.f);
	mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);
	material->SetSpecular(glm::vec3(specular.r, specular.g, specular.b));

	float shininess = 0.0f;
	mat->Get(AI_MATKEY_SHININESS, shininess);
	material->SetSpecularExponent(shininess);

	if (!m_materialLibrary)
		m_materialLibrary = new MaterialLibrary();

	m_materialLibrary->SetMaterial(material);

	return textures;
}
