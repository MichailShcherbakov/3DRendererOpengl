#ifndef _REFERENCE_GRID_H_
#define _REFERENCE_GRID_H_

#include "IRenderListener.h"
#include "GL/glew.h"

class ReferenceGrid : public IRenderListener
{
public:
	ReferenceGrid(float width, float length);
	~ReferenceGrid();

public:
	// IRenderListener
	virtual void Draw(Shader& shader) override;
	// ~IRenderListener

public:
	void Initialize();

private:
	float m_width;
	float m_length;
};

#endif // _REFERENCE_GRID_H_

