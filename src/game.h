#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>

#include "game_level.h"
#include "sprite_renderer.h"

enum GameState 
{
    GAME_MENU,
    GAME_PLAY,
    GAME_OVER,
};

class Game
{
public:
    GameState State;   
    GLboolean Keys[1024];
    GLboolean KeysProcessed[1024];
    GLuint Width, Height;
    std::vector<GameLevel> Levels;
    GLuint CurLevel;

    Game(GLuint width, GLuint height);
    ~Game();
    void Init();
    void ProcessInput();
    void MovePlayer(int dx, int dy);
    void Update(GLfloat dt);
    void Render();
    void Undo();

private:
    SpriteRenderer *SpriteRenderer;
};

#endif
