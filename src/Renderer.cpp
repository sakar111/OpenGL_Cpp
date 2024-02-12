#include "Renderer.h"

#include <iostream>

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::cout << "OPENGL ERROR :" << std::endl << message << std::endl;
	__debugbreak();

}

void Renderer::Clear(glm::vec3& color_RGB) const
{
	glClearColor(color_RGB.x / 255.0f, color_RGB.y / 255.0f, color_RGB.z / 255.0f, 1.0f);

	//glClearColor(0.90f, 1.0f, 1.0f, 1.0f);	// celeste polvere (powdery) 
	//glClearColor(0.8f, 1.0f, 1.0f, 1.0f);		// celeste pallido (pale) 
	//glClearColor(0.8f, 0.9f, 0.9f, 1.0f);		// celeste velato (veiled / overcast)
	//glClearColor(0.7f, 1.0f, 1.0f, 1.0f);		// celeste (sky blue, heavenly blue)
	//glClearColor(0.5f, 0.8f, 0.8f, 1.0f);		// celeste opaco (opaque)
	//glClearColor(0.0f, 0.75f, 1.0f, 1.0f);	//deep sky blue

	//glClearColor(0.45f, 0.82f, 0.98f, 1.0f);	//custom picked value


	//glClear(GL_COLOR_BUFFER_BIT);

}
/*
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	va.Bind();
	ib.Bind();
	shader.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
*/