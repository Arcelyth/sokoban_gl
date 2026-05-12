#include "game_object.h"

GameObject::GameObject() 
    : Position(0, 0), Size(1, 1), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite() 
{
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color, glm::vec2 velocity) 
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite)
{ 
}

void GameObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(Sprite, Position, Size, Rotation, Color);
}
