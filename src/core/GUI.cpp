#include "GUI.h"

void GUI::create(Registry &reg) {
    Vertex2D v0 = { glm::vec2(-1.0f, -1.0f), glm::vec2(0.537255f, 0.823529f) };
    Vertex2D v1 = { glm::vec2(1.0f, -1.0f), glm::vec2(0.537255f, 0.823529f) };
    Vertex2D v2 = { glm::vec2(-1.0f, 1.0f), glm::vec2(0.537255f, 0.823529f) };
    Vertex2D v3 = { glm::vec2(-1.0f, 1.0f), glm::vec2(0.537255f, 0.823529f) };
    Vertex2D v4 = { glm::vec2(1.0f, -1.0f), glm::vec2(0.537255f, 0.823529f) };
    Vertex2D v5 = { glm::vec2(1.0f, 1.0f), glm::vec2(0.537255f, 0.823529f) };

    std::vector<Vertex2D> vertices = { v0, v1, v2, v3, v4, v5 };

    const Entity panel = reg.create();
    reg.assign<Shader>(
        panel,
        "assets/shader/vertex2D.glsl",
        "assets/shader/fragment2D.glsl"
    );
    reg.assign<Renderable>(panel);
    reg.assign<Mesh2D>(
        panel,
        vertices
    );
    float width = 50.0f;
    float height = 50.0f;

    reg.assign<Transform2D>(
        panel,
        width,
        height,
        glm::vec2(2.0f, 2.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f)
    );
}
