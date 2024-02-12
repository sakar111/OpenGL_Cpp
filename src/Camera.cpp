#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 world_up, float fov, float yaw, float pitch, float keystroke_speed, float mouse_sensitivity)

	:KEYSTROKE_SPEED(keystroke_speed), MOUSE_SENSITIVITY(mouse_sensitivity),

	Yaw(yaw), Pitch(pitch),

	Position(position), Front(front), WorldUp(world_up), Up(1.0), Right(1.0),

	Fov(fov),

	mouse_enable(true)
{
	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	UpdateCameraVectors();
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = KEYSTROKE_SPEED * deltaTime;
	if (direction == Camera_Movement::forward)
		Position += Front * velocity;
	if (direction == Camera_Movement::backward)
		Position -= Front * velocity;
	if (direction == Camera_Movement::left)
		Position -= Right * velocity;
	if (direction == Camera_Movement::right)
		Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= MOUSE_SENSITIVITY;
	yoffset *= MOUSE_SENSITIVITY;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		else if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	Fov -= yoffset;
	if (Fov <= 1.0f)
		Fov = 1.0f;
	else if (Fov >= 45.0f)
		Fov = 45.0f;
}


void Camera::UpdateCameraVectors()
{	
	if (mouse_enable)
	{
		Front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front.y = sin(glm::radians(Pitch));
		Front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(Front);
	}
	
	else
	{
		Front = Front - Position;
	}
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}