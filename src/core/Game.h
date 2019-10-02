//
// Created by Júlio César Lopes on 02/10/19.
//

#ifndef CGAME_GAME_H
#define CGAME_GAME_H

#include <GL/glew.h>
#include "../util/registry.h"

class Game {
    Registry reg;
public:
    Game();
    void init();
    void update();
    void start();
    void clean();
    ~Game();
};


#endif //CGAME_GAME_H
