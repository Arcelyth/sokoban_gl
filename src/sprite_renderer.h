#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"
#include "vertex_buffer.h"


class SpriteRenderer
{
public:
    SpriteRenderer(Shader &shader);
    ~SpriteRenderer();
    void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec4 color = glm::vec4(1.0f));

private:
    Shader &shader; 
    GLuint vbo;
    GLuint quadVAO;
};

#endif
