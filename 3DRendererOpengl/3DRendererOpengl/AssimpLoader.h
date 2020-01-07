#ifndef _ASSIMP_LOADER_H_
#define _ASSIMP_LOADER_H_

#include "ILoader.h"
#include "MaterialLibrary.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class AssimpLoader : public ILoader
{
public:
	// ILoader
	virtual void Load(const std::string& path, std::vector<Mesh*>& meshes, IMaterialLibrary* library) override;
	// ~ILoader

private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture2D> loadMaterialTextures(aiMaterial* mat, aiTextureType type);

private:
	MaterialLibrary* m_materialLibrary;
	std::vector<Mesh*> m_meshes;
};

#endif // _ASSIMP_LOADER_H_
