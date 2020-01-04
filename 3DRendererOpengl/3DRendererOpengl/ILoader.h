#ifndef _I_LOADER_H_
#define _I_LOADER_H_

#include "IMaterialLibrary.h"
#include "Mesh.h"

struct ILoader
{
	virtual void Load(const std::string& path, std::vector<Mesh*>& meshes, IMaterialLibrary* library) = 0;
};

#endif // _I_LOADER_H_
