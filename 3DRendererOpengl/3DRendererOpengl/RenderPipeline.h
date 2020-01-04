#ifndef _RENDER_PIPELINE_H_
#define _RENDER_PIPELINE_H_

#include "Shader.h"
#include "IRenderListener.h"

#include <vector>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class RenderPipeline
{
public:
	void Render(Shader& shader);
	void AddListener(IRenderListener* listener);
	void RemoveListener(IRenderListener* listener);

private:
	std::vector<IRenderListener*> m_listeners;
};

#endif // _RENDER_PIPELINE_H_

