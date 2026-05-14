#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "shader.h"
#include "texture.h"

class ResourceManager 
{
public: 
    ResourceManager() = delete;
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture2D> Textures;

    static Shader LoadShader(const GLchar* v_shader_file, const GLchar* f_shader_file, const GLchar* g_shader_file, std::string name); 
    static Shader &GetShader(std::string name);

    static Texture2D LoadTexture(const GLchar *file, std::string name);
    static Texture2D &GetTexture(std::string name);
    
    static void Clear();

private: 
    static Shader loadShaderFromFile(const GLchar* v_shader_file, const GLchar* f_shader_file, const GLchar* g_shader_file = nullptr);
    static Texture2D loadTextureFromFile(const GLchar *file);
};

#endif
