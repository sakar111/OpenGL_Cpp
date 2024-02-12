#pragma once

#include "glm/glm.hpp"

class Light
{
public:
	glm::vec3 Color;
	glm::vec3 Position;
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;

	Light(glm::vec3 color, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
		:Color(color), Position(position), Ambient(ambient), Diffuse(diffuse), Specular(specular)
	{}
};



namespace Lights
{
	static glm::vec3 Coral(0.96f, 0.53f, 0.34f);
	static glm::vec3 MellowApricot(0.94f, 0.73f, 0.44f);
	static Light Sun(Coral, glm::vec3(-100.0f, 100.0f, 200.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	static Light light1(glm::vec3(0.94f, 0.73f, 0.44f), glm::vec3(-300.0f, 300.0f, 300.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
}