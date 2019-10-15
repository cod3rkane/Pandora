#ifndef CGAME_UIMANAGER_H
#define CGAME_UIMANAGER_H

#include <iostream>
#include <glm/vec2.hpp>
#include <vector>

#include "../util/registry.h"
#include "ui/UIComponent.h"
#include "../components/Render.h"
#include "../components/Shader.h"
#include "../components/Transform.h"

class UIManager {
    Registry* reg;
    std::vector<UI::Component> components;
public:
    UIManager();
    UIManager(Registry &reg);
    void createSimpleSquare();
    void addComponent(UI::Component component);
    void setReg(Registry &r);

    void init();
    void update();
    void render();
    void clean();
};

#endif // CGAME_UIMANAGER_H
