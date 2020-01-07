#ifndef _I_MATERIAL_LIBRARY_H_
#define _I_MATERIAL_LIBRARY_H_

#include "Material.h"
#include "Texture2D.h"

struct IMaterialLibrary
{
	virtual void Load(const std::string& path) = 0;
	virtual bool IsLoaded() const = 0;
	virtual bool IsEmpty() const = 0;
	virtual const Material* GetMaterial(const std::string& title) = 0;
	virtual void SetMaterial(const Material* material) = 0;

protected:
	bool m_isLoaded = false;
	std::vector<const Material*> m_materials;
	std::vector<const Texture2D*> m_textures;
};

#endif // _I_MATERIAL_LIBRARY_H_
