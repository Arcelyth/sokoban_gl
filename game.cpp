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
    ResourceManager::LoadTexture("./res/textures/Polygon1.png", "polygon");
    SpriteRenderer = new Sprite(ResourceManager::GetShader("sprite"));
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt)
{

}

void Game::Render()
{
    SpriteRenderer->DrawSprite(ResourceManager::GetTexture("polygon"), glm::vec2(200, 200), glm::vec2(300, 400), glm::radians(45.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
}
