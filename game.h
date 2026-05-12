#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>

#include "sprite.h"

enum GameState 
{
    GAME_MENU,
    GAME_PLAY,
    GAME_OVER,
};

class Game
{
public:
    GameState  State;   
    GLboolean  Keys[1024];
    GLuint     Width, Height;
    Game(GLuint width, GLuint height);
    ~Game();
    void Init();
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();

private:
    Sprite *SpriteRenderer;
};

#endif
