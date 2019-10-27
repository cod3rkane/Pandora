#include "UIComponent.h"

void UI::Component::addChildren(ComponentCore& component) {
    children.push_back(component);
}

std::vector<UI::ComponentCore> UI::Component::getChildrens() {
    return children;
}

void UI::Component::update(int windowWidth, int windowHeight, double mouseX, double mouseY, bool isMousePressed) {
    if (isInteractive) {
        std::cout << "x: " << mouseX << " Y: " << mouseY << std::endl;
        std::cout << "IsPressed: " << isMousePressed << std::endl;

        if (
            mouseX >= Position.x && mouseX <= (Position.x + width)
            && mouseY >= Position.y && mouseY <= (Position.y + height)
        ) {
            glm::vec3 currentColor = mesh.color;
            mesh.color = glm::vec4(currentColor, 0.3f);
        }
    }
}
