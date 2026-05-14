#ifndef SHADER_H
#define SHADER_H

#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    // Set uniform
    void SetFloat (const GLchar *name, GLfloat value); 
    void SetInteger (const GLchar *name, GLint value);
    void SetVector2f (const GLchar *name, GLfloat x, GLfloat y);
    void SetVector2f (const GLchar *name, const glm::vec2 &value);
    void SetVector3f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
    void SetVector3f (const GLchar *name, const glm::vec3 &value);
    void SetVector4f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void SetVector4f (const GLchar *name, const glm::vec4 &value);
    void SetMatrix4 (const GLchar *name, const glm::mat4 &matrix);
       
private: 
    void checkCompileError(GLuint shader, std::string type);
};

#endif
