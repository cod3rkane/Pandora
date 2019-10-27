#ifndef CGAME_UIMANAGER_H
#define CGAME_UIMANAGER_H

#include <iostream>
#include <glm/vec2.hpp>
#include <vector>

#include "../util/registry.h"
#include "ui/UIComponent.h"
#include "Shader.h"
#include "../components/Render.h"
#include "../components/Transform.h"

class UIManager {
    Registry* reg;
    GLuint vaoID;
    GLuint vboID;
    Core::Shader shader2d;
    GLuint tmBufferID;
    std::vector<UI::Component> components;
public:
    UIManager();
    UIManager(Registry &reg);
    void addComponent(UI::Component component);
    void setReg(Registry &r);
    void setupComponents();

    void init();
    void update(float deltaTime, int windowWidth, int windowHeight);
    void render(float deltaTime, int windowWidth, int windowHeight);
    void clean();
};

#endif // CGAME_UIMANAGER_H
