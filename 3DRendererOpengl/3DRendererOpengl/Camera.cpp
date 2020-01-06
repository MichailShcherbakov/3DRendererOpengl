#include "StdAfx.h"
#include "Camera.h"

Camera::Camera()
{
	Update();
}

glm::mat4 Camera::MakeViewMatrix() const
{
	/*glm::mat4 rotationMatrix = glm::identity<glm::mat4>();
	glm::mat4 translationMatrix = glm::identity<glm::mat4>();

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(this->m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(this->m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(this->m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	translationMatrix = glm::translate(translationMatrix, this->m_position);

	return rotationMatrix * translationMatrix;*/

	return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::MakeProjectionMatrix() const
{
	return glm::perspective(glm::radians(m_zoom), m_aspect, 0.1f, 100.0f);
}

void Camera::SetAspect(float width, float height)
{
	m_aspect = width / height;
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (m_zoom >= 1.0f && m_zoom <= 45.0f)
		m_zoom -= yoffset;
	if (m_zoom <= 1.0f)
		m_zoom = 1.0f;
	if (m_zoom >= 45.0f)
		m_zoom = 45.0f;
}

glm::vec3 Camera::GetPosition() const
{
	return m_position;
}

void Camera::Update()
{
	/*if (IsMoving())
	{
		glm::vec3 movementVectorLocal = glm::vec3(
			(float)this->m_movement.x * ((this->m_movementSpeed / 1000.0f) * deltaMs),
			(float)this->m_movement.y * ((this->m_movementSpeed / 1000.0f) * deltaMs),
			(float)this->m_movement.z * ((this->m_movementSpeed / 1000.0f) * deltaMs)
		);

		glm::vec3 movementVectorGlobal = glm::vec3(
			(cos(glm::radians(this->m_rotation.y)) * movementVectorLocal.x) - (sin(glm::radians(this->m_rotation.y)) * movementVectorLocal.z),
			(cos(glm::radians(this->m_rotation.x)) * movementVectorLocal.y) + (sin(glm::radians(this->m_rotation.x)) * movementVectorLocal.z),
			(sin(glm::radians(this->m_rotation.y)) * movementVectorLocal.x) + (cos(glm::radians(this->m_rotation.y)) * movementVectorLocal.z)
		);

		m_position += movementVectorGlobal;
	}*/

	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::ProcessKeyboard(ECameraMovement direction, float deltaTime)
{
	float velocity = m_movementSpeed * deltaTime;
	if (direction == ECameraMovement::FORWARD)
		m_position += m_front * velocity;
	if (direction == ECameraMovement::BACKWARD)
		m_position -= m_front * velocity;
	if (direction == ECameraMovement::LEFT)
		m_position -= m_right * velocity;
	if (direction == ECameraMovement::RIGHT)
		m_position += m_right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	Update();
}

bool Camera::IsMoving() const
{
	return m_movement.x != 0 || m_movement.y != 0 || m_movement.z != 0;
}
