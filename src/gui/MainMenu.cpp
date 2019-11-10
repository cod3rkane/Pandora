//
// Created by cod3r on 11/10/19.
//

#include "MainMenu.h"

GUI::MainMenu::MainMenu() {

}

GUI::MainMenu::MainMenu(UIManager *manager) {

}

void GUI::MainMenu::init(UIManager &manager) {
    uiManager = &manager;
    const float btnSize = 250.0f;

    auto* bgConstraint = new UI::Constraints();
    bgConstraint->setWidth(UI::ConstraintsType::PERCENTAGE, 100);
    bgConstraint->setHeight(UI::ConstraintsType::PERCENTAGE, 100);
    bgConstraint->setY(UI::ConstraintsType::PIXEL, 0);
    bgComponent->setConstraints(bgConstraint);
    bgComponent->setColorMesh(glm::vec4(0.219608f, 0.780392f, 0.596078f, 1.0f));
    uiManager->addComponent(bgComponent);

    auto* newGameConstraint = new UI::Constraints();
    newGameConstraint->setY(UI::ConstraintsType::CENTER, -50);
    newGameBtn->setConstraints(newGameConstraint);
    newGameBtn->setColorMesh(glm::vec4(0.207843f, 0.694118f, 0.831373f, 1.0f));
    newGameBtn->setWidth(btnSize);
    uiManager->addComponent(newGameBtn);

    auto* savedGameConstraint = new UI::Constraints();
    savedGameConstraint->setY(UI::ConstraintsType::CENTER, 10);
    savedGameBtn->setConstraints(savedGameConstraint);
    savedGameBtn->setColorMesh(glm::vec4(0.207843f, 0.694118f, 0.831373f, 1.0f));
    savedGameBtn->setWidth(btnSize);
    uiManager->addComponent(savedGameBtn);

    auto* exitGameConstraint = new UI::Constraints();
    exitGameConstraint->setY(UI::ConstraintsType::CENTER, 70);
    exitGameBtn->setConstraints(exitGameConstraint);
    exitGameBtn->setColorMesh(glm::vec4(0.207843f, 0.694118f, 0.831373f, 1.0f));
    exitGameBtn->setWidth(btnSize);
    uiManager->addComponent(exitGameBtn);
}

GUI::MainMenu::~MainMenu() {

}

void GUI::MainMenu::update() {

}

void GUI::MainMenu::render() {

}

void GUI::MainMenu::clean() {

}
