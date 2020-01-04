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
	// ~IRenderListener

public:
	void Initialize(float size, const CubeTexture& diffuseMap);

private:
	GLuint m_VAO;
	CubeTexture m_diffuseMap;
};

#endif // _SKY_BOX_H_
