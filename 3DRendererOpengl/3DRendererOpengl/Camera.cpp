#include "StdAfx.h"
#include "Camera.h"

#include "glfw3.h"

glm::mat4 Camera::MakeViewMatrix()
{
	glm::mat4 rotationMatrix = glm::identity<glm::mat4>();
	glm::mat4 translationMatrix = glm::identity<glm::mat4>();

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(this->m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(this->m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(this->m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	translationMatrix = glm::translate(translationMatrix, this->m_position);

	return rotationMatrix * translationMatrix;
}

glm::mat4 Camera::MakeTargetViewMatrix(glm::vec3 posTarget)
{
	return glm::lookAt(m_position, posTarget, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::MakeProjectionMatrix()
{
	return glm::perspective(m_FOV, m_aspectRatio, m_zNear, m_zFar);
}

void Camera::UpdatePosotion(float deltaMs)
{
	if (IsMoving())
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
	}
}

void Camera::ProcessMouseMovement(float posX, float posY)
{
	float deltaX = mouseY - posY;
	float deltaY = mouseX - posX;

	m_rotation.x -= deltaX * m_mouseSensitivity;
	m_rotation.y -= deltaY * m_mouseSensitivity;
	
	mouseX = posX;
	mouseY = posY;
}

void Camera::ProcessMousePosition(float posX, float posY)
{
	mouseX = posX;
	mouseY = posY;
}

void Camera::ProcessKeyboard(ECameraMovement direction, bool reset)
{
	switch (direction)
	{
	case ECameraMovement::FORWARD:
		if (reset)
			m_movement.z = 0;
		else
			m_movement.z++;
		break;
	case ECameraMovement::BACKWARD:
		if (reset)
			m_movement.z = 0;
		else
			m_movement.z--;
		break;
	case ECameraMovement::LEFT:
		if (reset)
			m_movement.x = 0;
		else
			m_movement.x--;
		break;
	case ECameraMovement::RIGHT:
		if (reset)
			m_movement.x = 0;
		else
			m_movement.x++;
		break;
	}
}

glm::vec3 Camera::Position()
{
	return m_position;
}

bool Camera::IsMoving()
{
	return m_movement.x != 0 || m_movement.y != 0 || m_movement.z != 0;
}
