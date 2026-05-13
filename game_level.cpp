#include "game_level.h"
#include "game_object.h"

#include <fstream>
#include <sstream>

GameLevel::GameLevel(glm::vec2 playerSize) : PlayerSize(playerSize), PlayerPos(glm::vec2(0, 0)), PlayerGPos(glm::vec2(0, 0)) {}

void GameLevel::Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight, GLuint offsetX, GLuint offsetY)
{
    Items.clear();
    char itemCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<char>> itemData;
    LevelSize = glm::vec2(levelWidth, levelHeight);
    Offset = glm::vec2(offsetX, offsetY);
    if (fstream)
    {
        while (std::getline(fstream, line)) 
        {
            std::istringstream sstream(line);
            std::vector<char> row;
            while (sstream >> itemCode) 
                row.push_back(itemCode);
            itemData.push_back(row);
        }
        if (itemData.size() > 0)
            init(itemData);
    }
    Map = glm::vec2(itemData[0].size(), itemData.size());
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
    for (GameObject &items: Items)
        items.Draw(renderer);
    Player->Draw(renderer);
}

GLboolean GameLevel::IsPass()
{
    return GL_FALSE;
}

void GameLevel::init(std::vector<std::vector<char>> itemData)
{
    GLuint height = itemData.size();
    GLuint width = itemData[0].size();
    GLuint GridWidth = LevelSize.x / static_cast<GLfloat>(width);
    GLuint GridHeight = LevelSize.y / static_cast<GLfloat>(height);
    GridSize = glm::vec2(GridWidth, GridHeight);    
    // Initialize level items based on itemData		
    for (GLuint y = 0; y < height; ++y)
    {
        for (GLuint x = 0; x < width; ++x)
        {
            glm::vec2 pos(Offset.x + GridWidth * x, Offset.y + GridHeight * y);
            glm::vec2 size(GridWidth, GridHeight);
            
            Texture2D texture;
  
            if (itemData[y][x] == 'W')
                texture = ResourceManager::GetTexture("Wall");
            else if (itemData[y][x] == 'E')
                texture = ResourceManager::GetTexture("Target");
            else if (itemData[y][x] == 'S') 
            {
                PlayerPos = pos + glm::vec2((GridWidth - static_cast<GLfloat>(PlayerSize.x))/ 2, (GridHeight - static_cast<GLfloat>(PlayerSize.y)) /2);
                texture = ResourceManager::GetTexture("Tile");
                Player = new GameObject(PlayerPos, glm::vec2(x, y), PlayerSize, ResourceManager::GetTexture("Player"));
            }                
            else
                texture = ResourceManager::GetTexture("Tile");

            GameObject obj(pos, glm::vec2(x, y), size,  texture, glm::vec4(0.8f, 0.8f, 0.7f, 1.0));
            Items.push_back(obj);
        }
    }

}
