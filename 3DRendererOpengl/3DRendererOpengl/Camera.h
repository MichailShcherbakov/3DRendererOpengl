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
	Camera();

public:
	glm::mat4 MakeViewMatrix() const;
	glm::mat4 MakeProjectionMatrix() const;
	void SetAspect(float width, float height);
	glm::vec3 GetPosition() const;

	bool IsMoving() const;
	void Update();

	void ProcessKeyboard(ECameraMovement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset);
	void ProcessMouseScroll(float yoffset);

	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::i8vec3 m_movement = glm::i8vec3(0, 0, 0);
	glm::vec3 m_rotation = glm::vec3(0.0f, 180.0f, 0.0f);

	float m_movementSpeed = 2.0f;
	float m_mouseSensitivity = 0.3f;
	float m_aspect = 1.0f;

	glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_right = glm::vec3(0.0f, 0.0f, 0.0f);

	float m_zoom = 45.0f;
	float m_yaw = -90.0f;
	float m_pitch = 0.0f;

};

#endif // _CAMERA_H_
