//
// Created by Júlio César Lopes on 02/10/19.
//

#ifndef CGAME_GAME_H
#define CGAME_GAME_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../util/registry.h"
#include "../util/Camera.h"

class Game {
    Registry reg;
    Camera playerCamera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
public:
    Game();
    void init();
    void update(float deltaTime, int windowWidth, int windowHeight);
    void start();
    void clean();
    ~Game();
};


#endif //CGAME_GAME_H
