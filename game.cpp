#include "game.h"
#include "GLFW/glfw3.h"
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
    ResourceManager::LoadTexture("./res/textures/Player.png", "Player");
    ResourceManager::LoadTexture("./res/textures/Box.png", "Box");
    // Load levels
    GameLevel one;

    GLuint LWidth = Width * 0.6;
    GLuint LHeight = Height * 0.6;
    GLuint offsetX = (Width - LWidth) / 2;
    GLuint offsetY = (Height - LHeight) / 2;
    one.Load("./levels/level1.txt", LWidth, LHeight, offsetX, offsetY);
    Levels.push_back(one);
    CurLevel = 0;
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput()
{
    if (State == GAME_PLAY) 
    {
        GameLevel &level = Levels[CurLevel];
        GameObject *player = level.Player;
        if (Keys[GLFW_KEY_A] && !KeysProcessed[GLFW_KEY_A])
        {

            if (player->GPosition.x > 0)
            {
                player->Position.x -= level.GridSize.x;
                player->GPosition.x--; 
            }
            KeysProcessed[GLFW_KEY_A] = GL_TRUE;
        }
        if (Keys[GLFW_KEY_D] && !KeysProcessed[GLFW_KEY_D])
        {

            if (player->GPosition.x < level.Map.x - 1)
            {
                player->Position.x += level.GridSize.x;
                player->GPosition.x++; 
            }
            KeysProcessed[GLFW_KEY_D] = GL_TRUE;
        }
        if (Keys[GLFW_KEY_W] && !KeysProcessed[GLFW_KEY_W])
        {

            if (player->GPosition.y > 0)
            {
                player->Position.y -= level.GridSize.y;
                player->GPosition.y--; 
            }
            KeysProcessed[GLFW_KEY_W] = GL_TRUE;
        }
        if (Keys[GLFW_KEY_S] && !KeysProcessed[GLFW_KEY_S])
        {

            if (player->GPosition.y < level.Map.y - 1)
            {
                player->Position.y += level.GridSize.y;
                player->GPosition.y++; 
            }
            KeysProcessed[GLFW_KEY_S] = GL_TRUE;
        }

    }
}

void Game::Render()
{
    if (State == GAME_PLAY) 
    {
        SpriteRenderer->DrawSprite(ResourceManager::GetTexture("Background"), glm::vec2(0, 0), glm::vec2(Width,Height), glm::radians(0.0f));
        Levels[CurLevel].Draw(*SpriteRenderer);
    }
}
