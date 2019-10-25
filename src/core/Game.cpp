//
// Created by Júlio César Lopes on 02/10/19.
//

#include "Game.h"

#include <entt/entt.hpp>

#include "../system/transformations.h"
#include "../system/interactions.h"
#include "../components/Shader.h"
#include "../components/Render.h"
#include "../components/Transform.h"
#include "../util/Camera.h"
#include "Terrain.h"
#include "ui/UIComponent.h"

Game::Game() {
    Camera playerCamera(glm::vec3(1.7f, 3.31f, 0.73f), glm::vec3(0.0f, 1.0f, 0.0f), -1.64f, -23.71f);
    entt::service_locator<Camera>::set(playerCamera);
}

Game::~Game() {

}

void Game::init(GLFWwindow* mainWindow) {
    window = mainWindow;

    createSimpleTerrain(reg);
    makeTree(reg, glm::vec3(6.0f, -0.2f, 4.0f));
    makeTree(reg, glm::vec3(8.0f, -0.2f, 1.0f));
    makeTree(reg, glm::vec3(10.0f, -0.2f, 2.0f));
    makeTree(reg, glm::vec3(8.0f, -0.2f, 2.0f));
    makeTree(reg, glm::vec3(6.0f, -0.2f, 2.25f));
    makeTree(reg, glm::vec3(8.8f, -0.2f, -2.2f));
    makeTree(reg, glm::vec3(10.2f, -0.2f, 1.4f));

    uiManager.setReg(reg);
    uiManager.init();
    
    UI::Component panel;
    panel.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    uiManager.addComponent(panel);

    for (int i = 0; i < 10; i++) {
        UI::Component panel2;
        panel2.setPosition(glm::vec3(i * 50.0f, i * 50.0f, 0.0f));
        uiManager.addComponent(panel2);
    }

    // @TODO once we've component to setup.
    uiManager.setupComponents();

    System::shader(reg);
}

void Game::update(float deltaTime, int windowWidth, int windowHeight) {
    // get inputs
    // create world
    System::preRender(reg);
    
    uiManager.update(deltaTime, windowWidth, windowHeight);
    System::userInputs(reg, window, deltaTime);
    System::transformations(reg, deltaTime, windowWidth, windowHeight);
}

void Game::start(float deltaTime, int windowWidth, int windowHeight) {
    // game loop
    // render things
    // Load Systems
    System::render(reg, deltaTime, windowWidth, windowHeight);
    uiManager.render(deltaTime, windowWidth, windowHeight);
}

void Game::clean() {
    uiManager.clean();
    System::cleanRender(reg);
}
