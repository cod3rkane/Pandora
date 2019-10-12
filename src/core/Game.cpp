//
// Created by Júlio César Lopes on 02/10/19.
//

#include "Game.h"

#include <entt/entt.hpp>

#include "../system/render.h"
#include "../system/transformations.h"
#include "../system/interactions.h"
#include "../components/Shader.h"
#include "../components/Render.h"
#include "../components/Transform.h"
#include "../util/Camera.h"
#include "Terrain.h"

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
    makeTree(reg, glm::vec3(9.5f, -0.2f, -2.0f));

    System::shader(reg);
    System::preRender(reg);
}

void Game::update(float deltaTime, int windowWidth, int windowHeight) {
    // get inputs
    // create world

    System::userInputs(reg, window, deltaTime);
    System::transformations(reg, windowWidth, windowHeight);
}

void Game::start() {
    // game loop
    // render things
    // Load Systems
    System::render(reg);
}

void Game::clean() {
    System::cleanRender(reg);
}
