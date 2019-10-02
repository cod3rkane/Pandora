//
// Created by Júlio César Lopes on 02/10/19.
//

#ifndef CGAME_GAME_H
#define CGAME_GAME_H

#include <GL/glew.h>
#include "../util/registry.h"

class Game {
    Registry reg;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    int shaderProgram;
public:
    Game();
    void init();
    void update();
    void start();
    ~Game();
};


#endif //CGAME_GAME_H
