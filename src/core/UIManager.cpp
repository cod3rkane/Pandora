#include "UIManager.h"

UIManager::UIManager() {};

UIManager::UIManager(Registry &reg) {
    this->reg = &reg;
}

void UIManager::createSimpleSquare() {
    Vertex2D v0 = { glm::vec2(-1.0f, -1.0f), glm::vec3(0.498039f, 0.596078f, 0.729412f) };
    Vertex2D v1 = { glm::vec2(1.0f, -1.0f), glm::vec3(0.498039f, 0.596078f, 0.729412f) };
    Vertex2D v2 = { glm::vec2(-1.0f, 1.0f), glm::vec3(0.498039f, 0.596078f, 0.729412f) };
    Vertex2D v3 = { glm::vec2(-1.0f, 1.0f), glm::vec3(0.498039f, 0.596078f, 0.729412f) };
    Vertex2D v4 = { glm::vec2(1.0f, -1.0f), glm::vec3(0.498039f, 0.596078f, 0.729412f) };
    Vertex2D v5 = { glm::vec2(1.0f, 1.0f), glm::vec3(0.498039f, 0.596078f, 0.729412f) };

    std::vector<Vertex2D> vertices = { v0, v1, v2, v3, v4, v5 };

    const Entity panel = reg->create();
    reg->assign<Shader>(
        panel,
        "assets/shader/vertex2D.glsl",
        "assets/shader/fragment2D.glsl"
    );
    reg->assign<Renderable>(panel);
    reg->assign<Mesh2D>(
        panel,
        vertices
    );
    float width = 50.0f;
    float height = 50.0f;

    reg->assign<Transform2D>(
        panel,
        width,
        height,
        glm::vec2(2.0f, 2.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f)
    );
}

void UIManager::addComponent(UI::Component component) {
    component.setEntity(reg->create());

    reg->assign<Shader>(component.getEntity(), "assets/shader/vertex2D.glsl", "assets/shader/fragment2D.glsl");
    reg->assign<Mesh2D>(component.getEntity(), component.getVertices());
    reg->assign<Transform2D>(
        component.getEntity(),
        component.getWidth(),
        component.getHeight(),
        component.getPosition(),
        component.getScale(),
        component.getRotation()
    );

    components.push_back(component);
}

void UIManager::setReg(Registry &r) {
    reg = &r;
}

void UIManager::init() {

}

void UIManager::update() {

}

void UIManager::render() {
    for (UI::Component e : components) {
        if (!reg->has<Renderable>(e.getEntity())) {
            reg->assign<Renderable>(e.getEntity());
        }
    }
}

void UIManager::clean() {
    
}
