#include "game_level.h"

#include <fstream>
#include <sstream>

void GameLevel::Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight)
{
    Items.clear();
    char itemCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<char>> itemData;
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
            init(itemData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
    for (GameObject &tile : Items)
        tile.Draw(renderer);
}

GLboolean GameLevel::IsPass()
{
    return GL_FALSE;
}

void GameLevel::init(std::vector<std::vector<char>> itemData, GLuint levelWidth, GLuint levelHeight)
{
    GLuint height = itemData.size();
    GLuint width = itemData[0].size();
    GLfloat unit_width = levelWidth / static_cast<GLfloat>(width);
    GLfloat unit_height = levelHeight / static_cast<GLfloat>(height); 

    // Initialize level items based on itemData		
    for (GLuint y = 0; y < height; ++y)
    {
        for (GLuint x = 0; x < width; ++x)
        {
            glm::vec2 pos(unit_width * x, unit_height * y);
            glm::vec2 size(unit_width, unit_height);
            
            Texture2D &texture = ResourceManager::GetTexture("Tile");
  
            if (itemData[y][x] == 'W')
                texture = ResourceManager::GetTexture("Wall");
            else if (itemData[y][x] == 'T')
                texture = ResourceManager::GetTexture("Target");
            else
                texture = ResourceManager::GetTexture("Tile");

            GameObject obj(pos, size, texture, glm::vec4(0.8f, 0.8f, 0.7f, 1.0));
            Items.push_back(obj);
        }
    }
}
