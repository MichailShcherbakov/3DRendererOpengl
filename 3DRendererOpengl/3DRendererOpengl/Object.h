#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ILoader.h"
#include "IRenderListener.h"
#include "BoundingBox.h"

class Object : public IRenderListener
{
public:
	Object();
	~Object() override;

public:
	// IRenderListener
	virtual void Draw(Shader& shader) override;
	virtual void MousePressEvent(MouseEvent* event) override;
	virtual void MouseReleaseEvent(MouseEvent* event) override;
	virtual void MouseMoveEvent(MouseEvent* event) override;
	virtual void KeyPressEvent(KeyEvent* event) override;
	virtual void KeyReleaseEvent(KeyEvent* event) override;
	// ~IRenderListener

public:
	void Initialize(const std::string& path);
	void SetLoader(ILoader* loader);
	void SetBoundingBox(BoundingBox* boundingBox);

private:
	ILoader* m_pLoader = nullptr;
	IMaterialLibrary* m_pMaterialLibrary = nullptr;
	BoundingBox* m_pBoundingBox = nullptr;
	std::vector<GLuint> m_VAOs;
	std::vector<GLsizei> m_numVertices;
	std::vector<std::string> m_materialsName;
	float minX, maxX, minY, maxY, minZ, maxZ;
	
};

#endif // _OBJECT_H_
