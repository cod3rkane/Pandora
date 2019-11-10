#include "Button.h"

void UI::Button::update() {
    UI::CoreComponent::runConstraints();
}


void UI::Button::update(double mouseX, double mouseY, bool isMousePressed) {
    UI::CoreComponent::runConstraints();

    if (interactive) {
        if (
                mouseX >= position.x
                && mouseX <= (position.x + width)
                && mouseY >= position.y
                && mouseY <= (position.y + height)
                ) {
            glm::vec4 currentColor = mesh.color;
            mesh.color = glm::vec4(currentColor.x, currentColor.y, currentColor.z, 0.3f);
            if (isMousePressed && callback != nullptr) {
                callback();
            }
        } else {
            mesh.color = glm::vec4(mesh.color.x, mesh.color.y, mesh.color.z, 1.0f);
        }
    }
}

void UI::Button::setCallback(const std::function<void(void)>& cb) {
    callback = cb;
}
