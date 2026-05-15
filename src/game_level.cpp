#include "game_level.h"
#include "game_object.h"

#include <cstddef>
#include <fstream>
#include <sstream>

GameLevel::GameLevel(glm::vec2 playerSize) : PlayerSize(playerSize), PlayerPos(glm::vec2(0, 0)), PlayerGPos(glm::vec2(0, 0)) {}

void GameLevel::Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight, GLuint offsetX, GLuint offsetY)
{
    Items.clear();
    Targets.clear();
    Boxes.clear();

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
    for (GameObject &box: Boxes)
        box.Draw(renderer);
    for (GameObject &target: Targets)
        target.Draw(renderer);
    for (GameObject &wall: Walls)
        wall.Draw(renderer);
    Player->Draw(renderer);
}

GLboolean GameLevel::IsPass()
{
    for (GameObject &target : Targets)
    {
        bool matched = false;

        for (GameObject &box : Boxes)
        {
            if (target.GPosition == box.GPosition)
            {
                matched = true;
                break;
            }
        }

        if (!matched)
            return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean GameLevel::IsWall(int nx, int ny) 
{
    for (GameObject &wall: Walls)
        if (wall.GPosition == glm::vec2(nx, ny))
            return GL_TRUE;
    return GL_FALSE;
}

int GameLevel::GetBox(int nx, int ny) 
{
    GLuint idx = 0;
    for (GameObject &box: Boxes)
    {
        if (box.GPosition == glm::vec2(nx, ny))
            return idx;
        idx++;
    }

    return -1;
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
            
            if (itemData[y][x] == 'W')
            {
                glm::vec2 p = GridToPos(WALL, glm::vec2(x, y));
                glm::vec2 s = GridSize * 1.0f;
                GameObject wall(p, glm::vec2(x, y), s, ResourceManager::GetTexture("Wall"), WALL);
                Walls.push_back(wall);
            }
            else if (itemData[y][x] == 'E')
            {
                glm::vec2 p = GridToPos(TARGET, glm::vec2(x, y));
                glm::vec2 s = GridSize * 0.6f;
                GameObject target(p, glm::vec2(x, y), s, ResourceManager::GetTexture("Target"), TARGET);
                Targets.push_back(target);
            }
            else if (itemData[y][x] == 'S') 
            {
                glm::vec2 p = GridToPos(PLAYER, glm::vec2(x, y));
                glm::vec2 s = GridSize * 0.75f;
                Player = new GameObject(p, glm::vec2(x, y), s, ResourceManager::GetTexture("Player"), PLAYER);
            }                
            else if (itemData[y][x] == '1') 
            {
                glm::vec2 p = GridToPos(BOX, glm::vec2(x, y));
                glm::vec2 s = GridSize * 0.85f;
                GameObject box(p, glm::vec2(x, y), s, ResourceManager::GetTexture("Box"), BOX);
                Boxes.push_back(box);
            }
            else if (itemData[y][x] == '2') 
            {
                glm::vec2 p = GridToPos(BOX, glm::vec2(x, y));
                glm::vec2 s = GridSize * 0.85f;
                GameObject box(p, glm::vec2(x, y), s, ResourceManager::GetTexture("Box2"), BOX2);
                Boxes.push_back(box);
            }
           
            GameObject obj(pos, glm::vec2(x, y), size, ResourceManager::GetTexture("Tile"), TILE, glm::vec4(0.8f, 0.8f, 0.7f, 1.0));
            Items.push_back(obj);
        }
    }

}

glm::vec2 GameLevel::GridToPos(ObjType ty, glm::vec2 pos) {
    glm::vec2 worldOrigin(Offset.x + GridSize.x * pos.x, Offset.y + GridSize.y * pos.y);
    
    float scale = 1.0f; 
    if (ty == PLAYER) 
        scale = 0.75f;
    else if (ty == BOX) 
        scale = 0.85f;
    else if (ty == TARGET) 
        scale = 0.60f;
    else if (ty == WALL)
        scale = 1.00f;

    glm::vec2 actualSize = GridSize * scale;
    glm::vec2 centerOffset = (GridSize - actualSize) * 0.5f;

    return worldOrigin + centerOffset;
}
