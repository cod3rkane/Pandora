#include "UIComponent.h"

void UI::Component::addChildren(ComponentCore& component) {
    children.push_back(component);
}

std::vector<UI::ComponentCore> UI::Component::getChildrens() {
    return children;
}
