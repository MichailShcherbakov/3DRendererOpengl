#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum class ECameraMovement : short 
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	glm::mat4 MakeViewMatrix();
	glm::mat4 MakeTargetViewMatrix(glm::vec3 posTarget);
	glm::mat4 MakeProjectionMatrix();
	void UpdatePosotion(float deltaMs);
	void ProcessMouseMovement(float posX, float posY);
	void ProcessMousePosition(float posX, float posY);
	void ProcessKeyboard(ECameraMovement direction, bool reset = false);
	glm::vec3 Position();
	bool IsMoving();

private:
	glm::vec3 m_position = glm::vec3(0.0f, 1.0f, 5.0f);
	glm::vec3 m_rotation = glm::vec3(0.0f, 180.0f, 0.0f);
	glm::i8vec3 m_movement = glm::i8vec3(0, 0, 0);

	float m_FOV = 30.0f;
	float m_aspectRatio = (float)1200 / (float)720;
	float m_zNear = 0.1f;
	float m_zFar = 256.0f;

	float m_movementSpeed = 2.0f;
	float m_mouseSensitivity = 0.3f;

	float mouseX = 0.0f;
	float mouseY = 0.0f;
};

#endif // _CAMERA_H_

