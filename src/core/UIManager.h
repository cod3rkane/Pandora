#ifndef CGAME_UIMANAGER_H
#define CGAME_UIMANAGER_H

#include <iostream>
#include <vector>
#include <entt/entt.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../util/registry.h"
#include "ui/UIComponent.h"
#include "ui/Button.h"
#include "Shader.h"
#include "../components/Render.h"
#include "../components/Transform.h"
#include "Window.h"
#include "../util/Camera.h"

class UIManager {
    Registry* reg;
    GLuint vaoID;
    GLuint vboID;
    Core::Shader shader2d;
    GLuint tmBufferID;
    GLuint colorBufferID;
    std::vector<UI::Component> components;
    std::vector<glm::vec4> colorMatrices;
    std::vector<glm::mat4> modelMatrices;
    glm::mat4 projection;
    glm::mat4 view;
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
