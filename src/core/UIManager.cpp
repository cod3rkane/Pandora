#include "UIManager.h"

UIManager::UIManager() {};

UIManager::UIManager(Registry &reg) {
    this->reg = &reg;
}

void UIManager::addComponent(UI::Component component) {
    components.push_back(component);
}

void UIManager::setReg(Registry &r) {
    reg = &r;
}

void UIManager::init() {
    shader2d = Core::Shader("assets/shader/vertex2D.glsl", "assets/shader/fragment2D.glsl");

    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);
}

void UIManager::update(float deltaTime, int windowWidth, int windowHeight) {
}

void UIManager::setupComponents() {
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    for (UI::Component component : components) {
        // std::vector<Vertex2D> vertices = component.getVertices();
        glBufferData(GL_ARRAY_BUFFER, component.vertices.size() * sizeof(Vertex2D), &component.vertices[0], GL_STATIC_DRAW);
    }

    // Vertex positions

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, Colors));
    glEnableVertexAttribArray(1);

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

void UIManager::render(float deltaTime, int windowWidth, int windowHeight) {
    shader2d.bind();
    glBindVertexArray(vaoID);
    // @TODO: create System to render 2D.
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::vector<glm::mat4> modelMatrices;
    for (UI::Component component : components) {
        glm::mat4 matrix = glm::mat4(1.0f);
        matrix = component.getModelMatrix(windowWidth, windowHeight);

        modelMatrices.push_back(matrix);
    }

    glUniform2f(glGetUniformLocation(shader2d.getProgramID(), "scale"), 1.0f, 1.0f);
    glBindBuffer(GL_ARRAY_BUFFER, tmBufferID);
    glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4), &modelMatrices[0], GL_DYNAMIC_DRAW);

    glDrawArraysInstanced(GL_TRIANGLES, 0, components.size() * 6, components.size());

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    shader2d.unbind();
}

void UIManager::clean() {
    shader2d.cleanUp();
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(1, &vboID);
}
