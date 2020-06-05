#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"


void Camera::UpdateCamVecs()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

Camera::Camera(float movespeed, glm::vec3 position, const glm::vec3& front, const glm::vec3& worldup, float yaw, float pitch, float mouseSensitivity, float scrollSensitivity) :
	m_MovementSpeed(movespeed),
	m_MouseSensitivity(mouseSensitivity),
	m_Yaw(yaw),
	m_Pitch(pitch),
	m_Roll(0),
	m_Pos(position),
	m_Front(glm::normalize(front)),
	m_WorldUp(glm::normalize(worldup)),
	m_Zoom(0),
	m_ScrollSensitivity(scrollSensitivity),
	m_LookAt(glm::mat4(1.0f)),
	m_step(0.2f)
{
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

Camera::~Camera()
{
}

void Camera::ProcessMouseInput(float xoffset, float yoffset, bool constrain_pitch)
{
	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	if (constrain_pitch)
	{
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
	}
}

glm::mat4 Camera::GetLookAt()
{
	UpdateCamVecs();
	return glm::lookAt(m_Pos, m_Pos + m_Front, m_Up);
}

void Camera::ProcessKeyboardInput(direction direction, float deltatime)
{
	float velocity = deltatime * m_MovementSpeed;

	if (direction == direction::FORWARD)
		m_Pos += m_Front * velocity;
	if (direction == direction::BACKWARD)
		m_Pos -= m_Front * velocity;
	if (direction == direction::LEFT)
		m_Pos -= m_Right * velocity;
	if (direction == direction::RIGHT)
		m_Pos += m_Right * velocity;
}
