#ifndef _MATERIAL_LIBRARY_H_
#define _MATERIAL_LIBRARY_H_

#include "IMaterialLibrary.h"
#include "Material.h"
#include "Texture2D.h"

class MaterialLibrary : public IMaterialLibrary
{
public:
	MaterialLibrary();
	MaterialLibrary(const std::string& path);
	~MaterialLibrary();

public:
	// IMaterialLibrary
	virtual void Load(const std::string& path) override;
	virtual bool IsLoaded() override;
	virtual const Material* GetMaterial(const std::string& title) override;
	//~IMaterialLibrary
	
private:
	void Clear();
};

#endif // _MATERIAL_LIBRARY_H_

