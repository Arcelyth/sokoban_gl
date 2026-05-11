#include "resource_manager.h"

#include <exception>
#include <fstream>
#include <sstream>
#include <iostream>

std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const GLchar* v_shader_file, const GLchar* f_shader_file, const GLchar* g_shader_file, std::string name)
{
    Shaders[name] = loadShaderFromFile(v_shader_file, f_shader_file, g_shader_file);
    return Shaders[name];
}

Shader ResourceManager::loadShaderFromFile(const GLchar* v_shader_file, const GLchar* f_shader_file, const GLchar* g_shader_file)
{
    std::string v_content, f_content, g_content;
    try 
    {
        std::ifstream v_file(v_shader_file);
        std::ifstream f_file(f_shader_file);
        std::ostringstream v_stream, f_stream;
        v_stream << v_file.rdbuf();
        f_stream << f_file.rdbuf();
        v_file.close();
        f_file.close();
        v_content = v_stream.str();
        f_content = f_stream.str();

        if (g_shader_file != nullptr) 
        {
            std::ifstream g_file(g_shader_file);
            std::ostringstream g_stream;
            g_stream << g_file.rdbuf();
            g_content = g_stream.str();
        }
    } 
    catch (std::exception e) 
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }

    const GLchar *g_code = nullptr;
    const GLchar *v_code = v_content.c_str();
    const GLchar *f_code = f_content.c_str();
    if (g_shader_file != nullptr) 
        const GLchar *g_code = g_content.c_str();

    Shader shader;
    shader.Run(v_code, f_code, g_code);
    return shader;
}

Shader ResourceManager::GetShader(std::string name) 
{
    return Shaders[name];
}

void ResourceManager::Clear()
{
    // delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
}
