#include <iostream>

#include "shader.h"

GLuint Shader::Compile(const GLchar* source, GLenum type) 
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    checkCompileError(shader, type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
    return shader;
}

void Shader::Run(const GLchar* vertex_source, const GLchar* fragment_source, const GLchar* geometry_source) 
{
    GLuint vert_s = Compile(vertex_source, GL_VERTEX_SHADER);
    GLuint frag_s = Compile(fragment_source, GL_FRAGMENT_SHADER);
    GLuint geo_s;
    if (geometry_source != nullptr) 
        geo_s = Compile(geometry_source, GL_GEOMETRY_SHADER);

    // Program
    ID = glCreateProgram();
    glAttachShader(ID, vert_s);
    glAttachShader(ID, frag_s);
    if (geometry_source != nullptr) 
        glAttachShader(ID, geo_s);
    glLinkProgram(ID);
    checkCompileError(ID, "PROGRAM");

    // Delete shaders
    glDeleteShader(vert_s);
    glDeleteShader(frag_s);
    if (geometry_source != nullptr) 
        glDeleteShader(geo_s);
}

void Shader::checkCompileError(GLuint shader, std::string type) 
{
    GLint success;
    if (type == "PROGRAM") 
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) 
        {
            GLsizei log_length = 0;
            GLchar infolog[1024];
            glGetShaderInfoLog(shader, 1024, &log_length, infolog);
     
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type
                << infolog << "\n ------------------------------" << std::endl; 
        }
    } 
    else 
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (success == GL_FALSE) 
        {
            GLsizei log_length = 0;
            GLchar infolog[1024];
            glGetProgramInfoLog(shader, 1024, &log_length, infolog);
     
            std::cout << "| ERROR::SHADER: Link-time error: Type: " << type
                << infolog << "\n ------------------------------" << std::endl; 
        }

    }
}

