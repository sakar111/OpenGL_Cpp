#include "IndexBuffer.h"

#include <GL/glew.h>

IndexBuffer::IndexBuffer(const void* data, unsigned int count)
	:m_Count(count)
{
	glGenBuffers(1, &m_RendererID);   // creates a single buffer object since 1 is passed and keeps its ID in the unsigned int variable passed
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);  // selects the buffer with passed ID
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);    //places the data into the selected buffer
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);  // selects the buffer with passed ID
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  // selects the buffer with passed ID
}