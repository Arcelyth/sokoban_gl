#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

class GameLevel
{
public:
    std::vector<GameObject> Items;
    GameLevel() { }
    void Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
    void Draw(SpriteRenderer &renderer);
    GLboolean IsPass();

private:
    void init(std::vector<std::vector<char>> tileData, GLuint levelWidth, GLuint levelHeight);
};

#endif
