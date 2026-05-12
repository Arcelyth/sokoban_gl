#include "game.h"
#include "glm/detail/func_trigonometric.hpp"
#include "resource_manager.h"

Game::Game(GLuint width, GLuint height) 
	: State(GAME_PLAY), Keys(), Width(width), Height(height) 
{ 

}

Game::~Game()
{
    delete SpriteRenderer;
}

void Game::Init()
{
    ResourceManager::LoadShader("./res/shader/shader.vert", "./res/shader/shader.frag", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(Width), static_cast<GLfloat>(Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("u_Sprite", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("u_Projection", projection);
    SpriteRenderer = new class SpriteRenderer(ResourceManager::GetShader("sprite"));

    // Load game textures
    ResourceManager::LoadTexture("./res/textures/background.png", "Background");
    ResourceManager::LoadTexture("./res/textures/Wall.png", "Wall");
    ResourceManager::LoadTexture("./res/textures/Tile.png", "Tile");
    ResourceManager::LoadTexture("./res/textures/Target.png", "Target");
    // Load levels
    GameLevel one;
    one.Load("./levels/level1.txt", Width, Height);
    Levels.push_back(one);
    CurLevel = 0;
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt)
{

}

void Game::Render()
{
    if (State == GAME_PLAY) 
    {
        SpriteRenderer->DrawSprite(ResourceManager::GetTexture("Background"), glm::vec2(0, 0), glm::vec2(Width,Height), glm::radians(0.0f));
        Levels[CurLevel].Draw(*SpriteRenderer);
    }
}
