//
// Created by cod3r on 10/28/19.
//

#include "CoreComponent.h"

const Mesh2D &UI::CoreComponent::getMesh() const {
    return mesh;
}

void UI::CoreComponent::setMesh(const Mesh2D &mesh) {
    CoreComponent::mesh = mesh;
}

float UI::CoreComponent::getWidth() const {
    return width;
}

void UI::CoreComponent::setWidth(float width) {
    CoreComponent::width = width;
}

float UI::CoreComponent::getHeight() const {
    return height;
}

void UI::CoreComponent::setHeight(float height) {
    CoreComponent::height = height;
}

const glm::vec3 &UI::CoreComponent::getPosition() const {
    return position;
}

void UI::CoreComponent::setPosition(const glm::vec3 &position) {
    CoreComponent::position = position;
}

GLfloat UI::CoreComponent::getRotate() const {
    return rotate;
}

void UI::CoreComponent::setRotate(GLfloat rotate) {
    CoreComponent::rotate = rotate;
}

Entity UI::CoreComponent::getEntity() const {
    return entity;
}

void UI::CoreComponent::setEntity(Entity entity) {
    CoreComponent::entity = entity;
}

bool UI::CoreComponent::isInteractive() const {
    return interactive;
}

void UI::CoreComponent::setInteractive(bool interactive) {
    CoreComponent::interactive = interactive;
}

const glm::mat4 UI::CoreComponent::getModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);

    model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0f));
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0f));

    model = glm::scale(model, glm::vec3(width, height, 1.0f));

    return model;
}

void UI::CoreComponent::setup() {
    Vertex2D v0 = { glm::vec2(0.0f, 1.0f) };
    Vertex2D v1 = { glm::vec2(1.0f, 0.0f) };
    Vertex2D v2 = { glm::vec2(0.0f, 0.0f) };
    Vertex2D v3 = { glm::vec2(0.0f, 1.0f) };
    Vertex2D v4 = { glm::vec2(1.0f, 1.0f) };
    Vertex2D v5 = { glm::vec2(1.0f, 0.0f) };

    mesh.vertices = { v0, v1, v2, v3, v4, v5 };
    mesh.color = glm::vec4(0.498039f, 0.596078f, 0.729412f, 1.0f);
    position = glm::vec3(0.0f, 0.0f, 0.0f);
}

UI::CoreComponent::CoreComponent() {
    setup();
}

void UI::CoreComponent::setColorMesh(const glm::vec4 &color) {
    mesh.color = color;
}

UI::CoreComponent::~CoreComponent() {

}
