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
    Core::Window Window;
    entt::service_locator<Camera>::set(playerCamera);
    entt::service_locator<Core::Window>::set(Window);
}

Game::~Game() {

}

void Game::init(GLFWwindow* mainWindow) {
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
    
    UI::Component panel;
    panel.setWidth(100.0f);
    panel.setPosition(glm::vec3(50.0f, 50.0f, 0.0f));
    uiManager.addComponent(panel);

    UI::Component panel2;
    panel2.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    panel2.setColorMesh(glm::vec4(0.0196078f, 0.909804f, 0.419608f, 0.3f));
    uiManager.addComponent(panel2);

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
    
    uiManager.update(deltaTime, windowWidth, windowHeight);
    System::userInputs(reg, deltaTime);
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
