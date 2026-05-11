#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "resource_manager.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    const char *title = "SokoBang";
    GLFWwindow *window = glfwCreateWindow(800, 600, title, nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback); 

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // The viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    const GLchar* v_shader_file = "./res/shader/shader.vert";
    const GLchar* f_shader_file = "./res/shader/shader.frag";
    Shader shader = ResourceManager::LoadShader(v_shader_file, f_shader_file, nullptr, "Shader");

    // vertices
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f, 
         0.0f,  0.0f, 0.0f, 
        0.5f, 0.5f, 0.0f, 
        -0.5, 0.5f, 0.0f,
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 4
    };

    // Buffer objects
    VertexBuffer vb(sizeof(vertices), vertices);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Vertex Array Object
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Element Buffer Object
    IndexBuffer ib(indices, 6);
    
    // unbind VAO
    glBindVertexArray(0);
    vb.Unbind();
    ib.Unbind();

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Render
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();

        GLfloat time_value = glfwGetTime();
        GLfloat green_value = (sin(time_value) / 2) + 0.5;
        // Set uniform
        shader.SetVector4f("u_Color", 0.5f, green_value, 0.8f, 1.0f);

        glBindVertexArray(VAO);
        // Draw triangle        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        // Show to the screen
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
}  
