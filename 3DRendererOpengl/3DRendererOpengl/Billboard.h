#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "Texture2D.h"
#include "IRenderListener.h"

class Billboard : public IRenderListener
{
public:
	~Billboard() override;

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
	void Initialize();
	void Process();
	void SetPosition(const glm::vec3& position);
	void SetSize(float_t width, float_t height);
	void SetTexture(const Texture2D& texture);

private:
	GLuint m_VAO = 0;
	GLuint m_VBO = 0;
	glm::vec3 m_position = glm::vec3(0.0f);
	glm::vec2 m_size = glm::vec2(1.0f, 1.0f);
	Texture2D m_texture;
};

#endif // _BILLBOARD_H_
