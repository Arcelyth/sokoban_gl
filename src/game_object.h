#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>

#include "texture.h"
#include "sprite_renderer.h"

enum ObjType 
{
    PLAYER,
    BOX,
    BOX2,
    WALL,
    TARGET,
    TILE,
};

class GameObject
{
public: 
    glm::vec2 Position, GPosition, Size, Velocity;
    glm::vec4 Color;
    GLfloat Rotation;
    Texture2D Sprite;
    ObjType Ty;
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 gPos, glm::vec2 size, Texture2D sprite, ObjType ty, glm::vec4 color = glm::vec4(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    virtual void Draw(SpriteRenderer &render);
};

#endif
