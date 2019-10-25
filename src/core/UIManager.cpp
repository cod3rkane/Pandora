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
    // component.setEntity(reg->create());

    // reg->assign<Mesh2D>(component.getEntity(), component.getVertices());
    // reg->assign<Transform2D>(
    //     component.getEntity(),
    //     component.getWidth(),
    //     component.getHeight(),
    //     component.getPosition(),
    //     component.getScale(),
    //     component.getRotation()
    // );

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

void UIManager::update() {
}

void UIManager::setupComponents() {
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    for (UI::Component component : components) {
        // std::vector<Vertex2D> vertices = component.getVertices();
        glBufferData(GL_ARRAY_BUFFER, component.vertices.size() * sizeof(Vertex2D), &component.vertices[0], GL_STATIC_DRAW);

        // Vertex positions
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)0);
        glEnableVertexAttribArray(0);

        // Vertex colors
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, Colors));
        glEnableVertexAttribArray(1);

        // Vertex textures
        // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, TexCoords));
        // glEnableVertexAttribArray(2);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // unbind VAO
    glBindVertexArray(0);
}

void UIManager::render() {
    shader2d.bind();
    glBindVertexArray(vaoID);
    // @TODO: create System to render 2D.
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    for (UI::Component component : components) {
        glm::vec3 scale = component.getScale();
        glUniform2f(glGetUniformLocation(shader2d.getProgramID(), "scale"), scale.x, scale.y);
        glm::mat4 matrix = component.getModelMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader2d.getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(matrix));    
        glDrawArrays(GL_TRIANGLES, 0, component.getVertices().size());
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
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
