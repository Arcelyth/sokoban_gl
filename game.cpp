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

void Game::MovePlayer(int dx, int dy)
{
    GameLevel &level = Levels[CurLevel];
    GameObject *player = level.Player;

    int nx = player->GPosition.x + dx;
    int ny = player->GPosition.y + dy;

    if (nx < 0 || nx >= level.Map.x)
        return;

    if (ny < 0 || ny >= level.Map.y)
        return;

    if (level.IsWall(nx, ny))
        return;

    GameObject *box = level.GetBox(nx, ny);

    if (box)
    {
        int bx = nx + dx;
        int by = ny + dy;

        if (bx < 0 || bx >= level.Map.x)
            return;

        if (by < 0 || by >= level.Map.y)
            return;

        if (level.IsWall(bx, by))
            return;
        if (level.GetBox(bx, by))
            return;

        box->GPosition.x = bx;
        box->GPosition.y = by;
        box->Position.x += dx * level.GridSize.x;
        box->Position.y += dy * level.GridSize.y;
    }

    player->GPosition.x = nx;
    player->GPosition.y = ny;

    player->Position.x += dx * level.GridSize.x;
    player->Position.y += dy * level.GridSize.y;
}

void Game::ProcessInput()
{
    if (State == GAME_PLAY) 
    {
        GameLevel &level = Levels[CurLevel];
        GameObject *player = level.Player;
        if (Keys[GLFW_KEY_A] && !KeysProcessed[GLFW_KEY_A])
        {
            MovePlayer(-1, 0);
            KeysProcessed[GLFW_KEY_A] = GL_TRUE;
        }
        if (Keys[GLFW_KEY_LEFT] && !KeysProcessed[GLFW_KEY_LEFT])
        {
            MovePlayer(-1, 0);
            KeysProcessed[GLFW_KEY_LEFT] = GL_TRUE;
        }
        if (Keys[GLFW_KEY_D] && !KeysProcessed[GLFW_KEY_D])
        {
            MovePlayer(1, 0);
            KeysProcessed[GLFW_KEY_D] = GL_TRUE;
        }
        if (Keys[GLFW_KEY_RIGHT] && !KeysProcessed[GLFW_KEY_RIGHT])
        {
            MovePlayer(1, 0);
            KeysProcessed[GLFW_KEY_RIGHT] = GL_TRUE;
        }
        if (Keys[GLFW_KEY_W] && !KeysProcessed[GLFW_KEY_W])
        {
            MovePlayer(0, -1);
            KeysProcessed[GLFW_KEY_W] = GL_TRUE;
        }
        if (Keys[GLFW_KEY_UP] && !KeysProcessed[GLFW_KEY_UP])
        {
            MovePlayer(0, -1);
            KeysProcessed[GLFW_KEY_UP] = GL_TRUE;
        }
        if (Keys[GLFW_KEY_S] && !KeysProcessed[GLFW_KEY_S])
        {
            MovePlayer(0, 1);
            KeysProcessed[GLFW_KEY_S] = GL_TRUE;
        }
        if (Keys[GLFW_KEY_DOWN] && !KeysProcessed[GLFW_KEY_DOWN])
        {
            MovePlayer(0, 1);
            KeysProcessed[GLFW_KEY_DOWN] = GL_TRUE;
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
