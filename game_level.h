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
    glm::vec2 PlayerPos, PlayerSize, PlayerGPos, GridSize, LevelSize, Offset, Map;
    GameObject *Player;
    GameLevel(glm::vec2 playerSize = glm::vec2(60, 60));
    void Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight, GLuint offsetX, GLuint offsetY);
    void Draw(SpriteRenderer &renderer);
    GLboolean IsPass();

private:
    void init(std::vector<std::vector<char>> tileData);
};

#endif
