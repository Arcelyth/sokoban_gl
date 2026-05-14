#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <GL/glew.h>

struct IndexBuffer 
{
public: 
    GLuint ID;
    unsigned int Count;

    IndexBuffer(const unsigned int *data, unsigned int count, GLenum usage = GL_STATIC_DRAW);
    ~IndexBuffer();
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer &operator=(const IndexBuffer&) = delete;

    void Bind() const;
    void Unbind() const;

private: 

};

#endif
