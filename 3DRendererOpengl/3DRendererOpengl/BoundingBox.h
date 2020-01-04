#ifndef _BOUNDING_BOX_H_
#define _BOUNDING_BOX_H_

#include "Shader.h"

class BoundingBox
{
public:
	BoundingBox();
	BoundingBox(float minX, float maxX,
		float minY, float maxY,
		float minZ, float maxZ);
public:
	void Process(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
	void Draw(Shader& shader);

private:
	glm::vec3 m_size;
	glm::vec3 m_center;
	glm::mat4 m_transform = glm::mat4(1.0f);
};


#endif // _BOUNDING_BOX_H_
