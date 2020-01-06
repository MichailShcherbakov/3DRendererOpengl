#ifndef _REFERENCE_GRID_H_
#define _REFERENCE_GRID_H_

#include "IRenderListener.h"
#include "GL/glew.h"

class ReferenceGrid : public IRenderListener
{
public:
	ReferenceGrid(float width, float length);
	~ReferenceGrid() override;

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

private:
	float m_width;
	float m_length;
};

#endif // _REFERENCE_GRID_H_

