#ifndef _SKY_BOX_H_
#define _SKY_BOX_H_

#include "IRenderListener.h"
#include "CubeTexture.h"

#include "GL/glew.h"

class Skybox : public IRenderListener
{
public:
	Skybox();
	Skybox(float size, const CubeTexture& diffuseMap);
	~Skybox();

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
	void Initialize(float size, const CubeTexture& diffuseMap);
	CubeTexture GetTexture() const;

private:
	GLuint m_VAO;
	GLuint m_VBO;
	CubeTexture m_diffuseMap;
};

#endif // _SKY_BOX_H_
