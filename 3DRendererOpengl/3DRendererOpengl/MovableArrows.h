#ifndef _MOVABLE_ARROWS_H_
#define _MOVABLE_ARROWS_H_

#include "IRenderListener.h"

class MovableArrows : public IRenderListener
{
public:
	MovableArrows();
	~MovableArrows() override;

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
	void RenderArrows();

private:
	glm::vec3 m_position;
};

#endif

