#include "UIManager.h"

UIManager::UIManager() {};

UIManager::UIManager(Registry &reg) {
    this->reg = &reg;
}

void UIManager::addComponent(UI::CoreComponent *component) {
    components.push_back(component);
}

void UIManager::setReg(Registry &r) {
    reg = &r;
}

void UIManager::init() {
    shader2d = Core::Shader("assets/shader/vertex2D.glsl", "assets/shader/fragment2D.glsl");

    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);

    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);
}

void UIManager::setupComponents() {
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    for (const UI::CoreComponent* component : components) {
        glBufferData(GL_ARRAY_BUFFER, component->getMesh().vertices.size() * sizeof(Vertex2D), &component->getMesh().vertices[0], GL_STATIC_DRAW);
    }

    // Vertex positions

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex colors
    glGenBuffers(1, &colorBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * components.size(), 0, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);

    // Vertex textures
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, TexCoords));
    // glEnableVertexAttribArray(2);

    glGenBuffers(1, &tmBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, tmBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * components.size(), 0, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 0));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 4));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 8));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 12));
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // unbind VAO
    glBindVertexArray(0);
}

void UIManager::update(float deltaTime, int windowWidth, int windowHeight) {
    // get only interactive items
    // std::vector<UI::Component> interactives;
    // std::copy_if(components.begin(), components.end(), std::back_inserter(interactives), [](UI::Component e) { return e.getIsInteractive(); });

    Core::Window* Window = &entt::service_locator<Core::Window>::ref();
    double mouseX, mouseY;
    glfwGetCursorPos(Window->getWindow(), &mouseX, &mouseY);
    int mouseLeftBtn = glfwGetMouseButton(Window->getWindow(), GLFW_MOUSE_BUTTON_LEFT);

    projection = glm::ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, -1.0f, 1.0f);

    // Update matrices always after changes
    for (UI::CoreComponent* component : components) {
        component->update(mouseX, mouseY, mouseLeftBtn == GLFW_PRESS);

        modelMatrices.push_back(component->getModelMatrix());
        colorMatrices.push_back(component->getMesh().color);
    }
}

void UIManager::render(float deltaTime, int windowWidth, int windowHeight) {
    shader2d.bind();
    glBindVertexArray(vaoID);
    // @TODO: create System to render 2D.
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUniformMatrix4fv(glGetUniformLocation(shader2d.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindBuffer(GL_ARRAY_BUFFER, tmBufferID);
    glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4), &modelMatrices[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
    glBufferData(GL_ARRAY_BUFFER, colorMatrices.size() * sizeof(glm::vec4), &colorMatrices[0], GL_DYNAMIC_DRAW);

    glDrawArraysInstanced(GL_TRIANGLES, 0, components.size() * 6, components.size());

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    shader2d.unbind();
    modelMatrices.clear();
    colorMatrices.clear();
}

void UIManager::clean() {
    shader2d.cleanUp();
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(1, &vboID);
}
