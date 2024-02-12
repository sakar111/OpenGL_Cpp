#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class Camera_Movement
{
	forward,
	backward,
	left,
	right
};

class Camera
{
private:
	const float KEYSTROKE_SPEED;
	const float MOUSE_SENSITIVITY;
	
	float Yaw;


	glm::vec3 WorldUp;
	glm::vec3 Up;
	glm::vec3 Right;

public:
	float Pitch;

	float Fov;
	glm::vec3 Position;
	glm::vec3 Front;

	bool mouse_enable;


public:
	Camera(glm::vec3 position, glm::vec3 front, glm::vec3 world_up, float fov, float yaw, float pitch, float keystroke_speed, float mouse_sensitivity);

	glm::mat4 GetViewMatrix();

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

	void ProcessMouseScroll(float yoffset);

private:
	void UpdateCameraVectors();

};