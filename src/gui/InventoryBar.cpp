//
// Created by cod3r on 11/10/19.
//

#include "InventoryBar.h"

GUI::InventoryBar::InventoryBar() {

}

void GUI::InventoryBar::update() {

}

void GUI::InventoryBar::init(UIManager &manager) {
    uiManager = &manager;

    UI::Constraints* buttonConstraint = new UI::Constraints();
    buttonConstraint->setX(UI::ConstraintsType::CENTER);
    buttonConstraint->setY(UI::ConstraintsType::PERCENTAGE, 99);
    button1->setConstraints(buttonConstraint);

    UI::Constraints* button2Constraint = new UI::Constraints();
    button2Constraint->setX(UI::ConstraintsType::CENTER, 60);
    button2Constraint->setY(UI::ConstraintsType::PERCENTAGE, 99);
    button2->setConstraints(button2Constraint);

    UI::Constraints* button3Constraint = new UI::Constraints();
    button3Constraint->setX(UI::ConstraintsType::CENTER, -60);
    button3Constraint->setY(UI::ConstraintsType::PERCENTAGE, 99);
    button3->setConstraints(button3Constraint);
}

GUI::InventoryBar::~InventoryBar() {
    clean();
}

void GUI::InventoryBar::render() {
    if (!hasCreated) {
        uiManager->addComponent(button1);
        uiManager->addComponent(button2);
        uiManager->addComponent(button3);
        hasCreated = true;
    }
}

void GUI::InventoryBar::clean() {
    uiManager->removeComponent(button1);
    uiManager->removeComponent(button2);
    uiManager->removeComponent(button3);
}
