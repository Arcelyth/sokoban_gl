#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>

class Shader
{
public:
    GLuint ID;

    Shader() {};
    // Use program
    Shader &Use();
    GLuint Compile(const GLchar* source, GLenum type);
    void Run(const GLchar* vertex_source, const GLchar* fragment_source, const GLchar* geometry_source);
    
private: 
    void checkCompileError(GLuint shader, std::string type);
};

#endif
