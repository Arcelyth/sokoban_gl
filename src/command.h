#ifndef COMMAND_H
#define COMMAND_H

#include "game_object.h"
#include <glm/glm.hpp>

struct Command 
{
public:
    glm::ivec2 PlayerPrev;
    glm::ivec2 BoxPrev;
    int BoxIdx;
    Command();

private: 
};

#endif
