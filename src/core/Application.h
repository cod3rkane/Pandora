//
// Created by Júlio César Lopes on 02/10/19.
//

#ifndef CGAME_APPLICATION_H
#define CGAME_APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include "Game.h"

class Application {
    GLFWwindow* window = nullptr;
    std::string title = "Pandora Project - Alpha 0.0.1";
    Game game;

public:
    Application();
    void init();
    void update();
    void start();
    ~Application();
};


#endif //CGAME_APPLICATION_H
