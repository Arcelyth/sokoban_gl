#include "glm/detail/type_mat.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

#include "resource_manager.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "glm/gtc/matrix_transform.hpp"

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

    glm::mat4 proj = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

    glm::mat4 mvp = proj * model * view;

    // The viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    const GLchar* v_shader_file = "./res/shader/shader.vert";
    const GLchar* f_shader_file = "./res/shader/shader.frag";
    Shader shader = ResourceManager::LoadShader(v_shader_file, f_shader_file, nullptr, "Shader");

    // vertices
//    GLfloat vertices[] = {
//        // pos              // texture 
//        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 
//         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
//         0.0f,  0.0f, 0.0f, 0.5f, 0.5f,  
//        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
//        -0.5, 0.5f, 0.0f, 0.0f, 1.0f,
//    };
    GLfloat vertices[] = {
        // pos                              // texture
        300.0f, 200.0f, 0.0f,   0.0f, 0.0f,
        500.0f, 200.0f, 0.0f,   1.0f, 0.0f,
        400.0f, 300.0f, 0.0f,   0.5f, 0.5f,
        500.0f, 400.0f, 0.0f,   1.0f, 1.0f,
        300.0f, 400.0f, 0.0f,   0.0f, 1.0f,
    };

    GLuint indices[] = {
        0, 1, 3,
        0, 3, 4
    };

    // Vertex Array Object
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Buffer objects
    VertexBuffer vb(sizeof(vertices), vertices);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Element Buffer Object
    IndexBuffer ib(indices, 6);
    
    // Unbind VAO
    glBindVertexArray(0);
    vb.Unbind();
    ib.Unbind();

    // Textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    const char *try_tex = "./res/textures/Polygon1.png";
    Texture2D texture = ResourceManager::LoadTexture(try_tex, "try");
    shader.Use();
    shader.SetInteger("polygon", 0);
    shader.SetMatrix4("u_MVP", mvp);

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
        texture.Bind(0);
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

