#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "shader.h"

class ResourceManager 
{
public: 
    static std::map<std::string, Shader> Shaders;

    static Shader LoadShader(const GLchar* v_shader_file, const GLchar* f_shader_file, const GLchar* g_shader_file, std::string name); 
    static Shader GetShader(std::string name);
    static void Clear();

private: 
    static Shader loadShaderFromFile(const GLchar* v_shader_file, const GLchar* f_shader_file, const GLchar* g_shader_file = nullptr);
};

#endif
