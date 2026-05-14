#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <GL/glew.h>

struct VertexBuffer 
{
public: 
    GLuint ID;

    VertexBuffer(GLsizeiptr size, const GLvoid *vertices, GLenum usage = GL_STATIC_DRAW);
    ~VertexBuffer();
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer &operator=(const VertexBuffer&) = delete;

    void Bind() const;
    void Unbind() const;

private: 

};

#endif
