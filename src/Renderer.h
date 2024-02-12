#pragma once

#include <GL/glew.h>

//#include "VertexArray.h"
//#include "IndexBuffer.h"
#include "Shader.h"

#include "glm/glm.hpp"

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void* userParam);

class Renderer
{
public:
	void Clear(glm::vec3& color_RGB) const;
	//void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};