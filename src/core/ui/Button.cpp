#include "Button.h"

void UI::Button::update() {

}


void UI::Button::update(double mouseX, double mouseY, bool isMousePressed) {
    if (interactive) {
        if (
                mouseX >= position.x
                && mouseX <= (position.x + width)
                && mouseY >= position.y
                && mouseY <= (position.y + height)
                ) {
            glm::vec4 currentColor = mesh.color;
            mesh.color = glm::vec4(currentColor.x, currentColor.y, currentColor.z, 0.3f);
        } else {
            mesh.color = glm::vec4(mesh.color.x, mesh.color.y, mesh.color.z, 1.0f);
        }
    }
}
