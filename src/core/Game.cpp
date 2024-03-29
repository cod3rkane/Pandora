//
// Created by Júlio César Lopes on 02/10/19.
//

#include "Game.h"

#include <entt/entt.hpp>

#include "../system/transformations.h"
#include "../system/interactions.h"
#include "Terrain.h"
#include "ui/Button.h"

Game::Game() {
    Camera playerCamera(glm::vec3(1.7f, 3.31f, 0.73f), glm::vec3(0.0f, 1.0f, 0.0f), -1.64f, -23.71f);
    Core::Window Window;
    entt::service_locator<Camera>::set(playerCamera);
    entt::service_locator<Core::Window>::set(Window);
}

Game::~Game() {

}

void Game::init(GLFWwindow* mainWindow, int windowWidth, int windowHeight) {
    Core::Window* Window = &entt::service_locator<Core::Window>::ref();
    Window->setWindow(mainWindow);

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

    mainMenu.init(uiManager, &currentState);
    inventoryBar.init(uiManager);

    // @TODO once we've component to setup.
    uiManager.setupComponents();

    System::shader(reg);
}

void Game::update(float deltaTime, int windowWidth, int windowHeight) {
    Core::Window* Window = &entt::service_locator<Core::Window>::ref();
    Window->setWidth(windowWidth);
    Window->setHeight(windowHeight);

    // get inputs
    // create world
    System::preRender(reg);

    switch (currentState) {
        case GameStateTypes::MAIN_MENU:
            mainMenu.update();
            break;
        case GameStateTypes::RUN:
            inventoryBar.render();
            System::userInputs(reg, deltaTime);
            System::transformations(reg, deltaTime, windowWidth, windowHeight);
            break;
        case GameStateTypes::PAUSE:
            break;
        default:
            break;
    }
    
    uiManager.update(deltaTime, windowWidth, windowHeight);
}

void Game::start(float deltaTime, int windowWidth, int windowHeight) {
    // game loop
    // render things
    // Load Systems

    switch (currentState) {
        case GameStateTypes::MAIN_MENU:
            // Draw MainMenu
            mainMenu.render();
            break;
        case GameStateTypes::RUN:
            // Start Timer
            System::render(reg, deltaTime, windowWidth, windowHeight);
            break;
        case GameStateTypes::PAUSE:
            // Stop Timer
            break;
        default:
            break;
    }

    uiManager.render(deltaTime, windowWidth, windowHeight);
}

void Game::clean() {
    mainMenu.clean();
    inventoryBar.clean();
    uiManager.clean();
    System::cleanRender(reg);
}
