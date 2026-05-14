#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"
#include "command.h"

class GameLevel
{
public:
    std::vector<GameObject> Items, Targets, Boxes, Walls;
    std::vector<Command> History;
    glm::vec2 PlayerPos, PlayerSize, PlayerGPos, GridSize, LevelSize, Offset, Map;
    GameObject *Player;
    GameLevel(glm::vec2 playerSize = glm::vec2(60, 60));
    void Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight, GLuint offsetX, GLuint offsetY);
    void Draw(SpriteRenderer &renderer);
    GLboolean IsPass();
    GLboolean IsWall(int nx, int ny);
    int GetBox(int nx, int ny);
    glm::vec2 GridToPos(ObjType ty, glm::vec2 pos);

private:
    void init(std::vector<std::vector<char>> tileData);
};

#endif
