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
#include "UIManager.h"
#include "../system/render.h"
#include "Window.h"

class Game {
    Registry reg;
    UIManager uiManager;
public:
    Game();
    void init(GLFWwindow* mainWindow);
    void update(float deltaTime, int windowWidth, int windowHeight);
    void start(float deltaTime, int windowWidth, int windowHeight);
    void clean();
    ~Game();
};


#endif //CGAME_GAME_H
