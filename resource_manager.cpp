#include "resource_manager.h"

#include <exception>
#include <fstream>
#include <sstream>
#include <iostream>

Shader ResourceManager::LoadShader(const GLchar* v_shader_file, const GLchar* f_shader_file, const GLchar* g_shader_file, std::string name)
{
    Shaders[name] = loadShaderFromFile(v_shader_file, f_shader_file, g_shader_file);
    return Shaders[name];
}

Shader loadShaderFromFile(const GLchar* v_shader_file, const GLchar* f_shader_file, const GLchar* g_shader_file)
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

    const GLchar *v_code = v_content.c_str();
    const GLchar *f_code = f_content.c_str();
    const GLchar *g_code = g_content.c_str();

    Shader shader;
    shader.Run(v_code, f_code, g_code != nullptr ? g_code: nullptr);
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
