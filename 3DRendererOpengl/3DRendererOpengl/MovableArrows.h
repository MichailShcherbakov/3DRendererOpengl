#ifndef _MOVABLE_ARROWS_H_
#define _MOVABLE_ARROWS_H_

#include "IRenderListener.h"

class MovableArrows : public IRenderListener
{
public:
	MovableArrows();

public:
	// IRenderListener
	virtual void Draw(Shader& shader) override;
	// ~IRenderListener

public:
	void Initialize();
	void RenderArrows();

private:
	glm::vec3 m_position;
};

#endif

