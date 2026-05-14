#include "index_buffer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count, GLenum usage) : Count(count) 
{
    glGenBuffers(1, &ID) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage);
}

IndexBuffer::~IndexBuffer() 
{
    glDeleteBuffers(1, &ID);
}

void IndexBuffer::Bind() const 
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBuffer::Unbind() const 
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
