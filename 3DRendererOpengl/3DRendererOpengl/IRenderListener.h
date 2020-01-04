#ifndef _I_RENDER_LISTENER_H_
#define _I_RENDER_LISTENER_H_

#include "Shader.h"

struct IRenderListener
{
	IRenderListener() { this->count++; this->objectID = this->count; }

	virtual void Draw(Shader& shader) = 0;

	static size_t count;

protected:
	size_t objectID = 0;
};

#endif // _I_RENDER_LISTENER_H_
