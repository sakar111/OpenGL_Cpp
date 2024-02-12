#pragma once

#include "glm/glm.hpp"
//#include "Texture.h"

#include <iostream>

class Material
{
public:
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Shininess;

	Material()
	{

	}

	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
		:Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess)
	{}
};



namespace Materials
{
	static Material material1(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
	static Material Emerald(glm::vec3(0.0215, 0.1745, 0.0215), glm::vec3(0.07568, 0.61424, 0.07568), glm::vec3(0.633, 0.727811, 0.633), 0.6);
	static Material Gold(glm::vec3(0.24725, 0.1995, 0.0745), glm::vec3(0.75164, 0.60648, 0.22648), glm::vec3(0.628281, 0.555802, 0.366065), 0.4);
	static Material RedPlastic(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.5, 0.0, 0.0), glm::vec3(0.7, 0.6, 0.6), .25);
}
/*
class LightingMap
{
public:
	Texture texture_diffuse;
	Texture texture_specular;
public:
	unsigned int DiffuseSlot;
	unsigned int SpecularSlot;
	float Shininess;

	LightingMap(std::string diffuse_path, std::string specular_path, unsigned int diffuseSlot, unsigned int specularSlot, float shininess)
		:texture_diffuse(diffuse_path), texture_specular(specular_path), DiffuseSlot(diffuseSlot), SpecularSlot(specularSlot), Shininess(shininess)
	{
		texture_diffuse.Bind(DiffuseSlot);
		texture_specular.Bind(SpecularSlot);
	}
};
*/