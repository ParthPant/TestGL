#pragma once

#include "glm/glm.hpp"


class Camera {
private:
	glm::vec3 m_Pos;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_WorldUp;
	glm::vec3 m_Right;

	float m_Pitch;
	float m_Yaw;
	float m_Roll;

	float m_MovementSpeed;
	float m_MouseSensitivity;
	
	float m_Zoom;
	float m_ScrollSensitivity;

	float m_step;

	glm::mat4 m_LookAt;

	void UpdateCamVecs();

public:

	 enum class direction {
	 	NONE = 0, UP, DOWN, RIGHT, LEFT, FORWARD, BACKWARD
	 };

	 Camera(float movespeed, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& front = glm::vec3(0.0f, 0.0f, 1.0f), const glm::vec3& worldup = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = 0.0f, float pitch = 0.0f, float mouseSensitivity = 0.1f, float scrollSensitivity = 1.0f);
	 ~Camera();

	 void ProcessKeyboardInput(direction direction, float deltatime);
	 void ProcessMouseInput(float xoffset, float yoffset, bool constrain_pitch);

	 glm::vec3 GetPosition() const { return m_Pos; };

	 glm::mat4 GetLookAt();

private:
	 direction m_direction = direction::NONE;
};