#include "VertexBuffer.h"

#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_RendererID);   // creates a single buffer object since 1 is passed and keeps its ID in the unsigned int variable passed
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);  // selects the buffer with passed ID
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);    //places the data into the selected buffer
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);  // selects the buffer with passed ID
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);  // selects the buffer with passed ID
}