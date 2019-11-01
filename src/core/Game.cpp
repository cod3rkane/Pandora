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

    UI::CoreComponent* button = new UI::Button();
    UI::Constraints* buttonConstraint = new UI::Constraints();
    buttonConstraint->setX(UI::ConstraintsType::CENTER);
    buttonConstraint->setY(UI::ConstraintsType::PERCENTAGE, 99);
    button->setConstraints(buttonConstraint);
    uiManager.addComponent(button);

    UI::CoreComponent* button2 = new UI::Button();
    UI::Constraints* button2Constraint = new UI::Constraints();
    button2Constraint->setX(UI::ConstraintsType::CENTER, 60);
    button2Constraint->setY(UI::ConstraintsType::PERCENTAGE, 99);
    button2->setConstraints(button2Constraint);
    uiManager.addComponent(button2);

    UI::CoreComponent* button3 = new UI::Button();
    UI::Constraints* button3Constraint = new UI::Constraints();
    button3Constraint->setX(UI::ConstraintsType::CENTER, -60);
    button3Constraint->setY(UI::ConstraintsType::PERCENTAGE, 99);
    button3->setConstraints(button3Constraint);
    uiManager.addComponent(button3);

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
