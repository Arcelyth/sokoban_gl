#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"

class GameObject
{
public: 
    glm::vec2 Position, Size, Velocity;
    glm::vec4 Color;
    GLfloat Rotation;
    Texture2D Sprite;
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color = glm::vec4(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    virtual void Draw(SpriteRenderer &render);
};

#endif
