#ifndef _OBJ_LOADER_H_
#define _OBJ_LOADER_H_

#include "ILoader.h"

class ObjLoader : public ILoader
{
public:
	// ILoader
	virtual void Load(const std::string& path, std::vector<Mesh*>& meshes, IMaterialLibrary* library) override;
	// ~ILoader

private:
	struct ObjMesh
	{
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;
		std::vector<Index> indices;
		std::string materialName;
	};
};

#endif // _OBJ_LOADER_H_

