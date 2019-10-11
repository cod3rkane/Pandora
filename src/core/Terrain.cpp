#include "Terrain.h"

#include <iostream>
#include <glm/ext.hpp>

#include "../components/Shader.h"
#include "../components/Render.h"
#include "../components/Transform.h"

void createSimpleTerrain(Registry &reg) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    const float SIZE = 40.0f;
    const int VERTEX_COUNT = 128;

    for (int z = 0; z < VERTEX_COUNT; z++) {
        for (int x = 0; x < VERTEX_COUNT; x++) {
            float xVert = (float) x / ((float)VERTEX_COUNT - 1) * SIZE;
            float zVert = (float) z / ((float)VERTEX_COUNT - 1) * SIZE;
            Vertex vertice = { glm::vec3(xVert, 0.0f, zVert), glm::vec3(0.15f, 0.7f, 0.26f), glm::vec2(1.0f, 1.0f) };
            vertices.push_back(vertice);
        }
    }

    for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
        for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
            int topLeft = (gz * VERTEX_COUNT) + gx;
            int topRight = topLeft +1;
            int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
            int bottomRight = bottomLeft + 1;
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }

    const Entity terrain = reg.create();
    reg.assign<Shader>(
        terrain,
        "assets/shader/vertex.glsl",
        "assets/shader/fragment.glsl"
    );
    reg.assign<Renderable>(terrain);
    reg.assign<Mesh>(
        terrain,
        vertices,
        indices
    );
    reg.assign<Transform>(
        terrain,
        glm::vec3(4.0f, 0.0f, -3.0f),
        100,
        100,
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.2f, 0.2f, 0.2f)
    );
}
