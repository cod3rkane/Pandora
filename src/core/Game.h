//
// Created by Júlio César Lopes on 02/10/19.
//

#ifndef CGAME_GAME_H
#define CGAME_GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../util/registry.h"

class Game {
    Registry reg;
    GLFWwindow* window;
public:
    Game();
    void init(GLFWwindow* window);
    void update(float deltaTime, int windowWidth, int windowHeight);
    void start();
    void clean();
    ~Game();
};


#endif //CGAME_GAME_H
