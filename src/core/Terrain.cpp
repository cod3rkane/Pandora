#include "Terrain.h"

#include <iostream>

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

void makeTree(Registry &reg, glm::vec3 position) {
    // top of tree
    Vertex v0 = {glm::vec3(-1.0f, 6.0f, 0.0f), glm::vec3(0.070f, 0.478f, 0.196f), glm::vec2(1.0f, 1.0f)};
    Vertex v1 = {glm::vec3(1.0f, 6.0f, 0.0f), glm::vec3(0.070f, 0.478f, 0.196f), glm::vec2(1.0f, 1.0f)};
    Vertex v2 = {glm::vec3(-1.0f, 3.0f, 0.0f), glm::vec3(0.070f, 0.478f, 0.196f), glm::vec2(1.0f, 1.0f)};
    Vertex v3 = {glm::vec3(1.0f, 3.0f, 0.0f), glm::vec3(0.070f, 0.478f, 0.196f), glm::vec2(1.0f, 1.0f)};
    Vertex v4 = {glm::vec3(-1.0f, 6.0f, -2.0f), glm::vec3(0.070f, 0.478f, 0.196f), glm::vec2(1.0f, 1.0f)};
    Vertex v5 = {glm::vec3(-1.0f, 3.0f, -2.0f), glm::vec3(0.070f, 0.478f, 0.196f), glm::vec2(1.0f, 1.0f)};
    Vertex v6 = {glm::vec3(1.0f, 6.0f, -2.0f), glm::vec3(0.070f, 0.478f, 0.196f), glm::vec2(1.0f, 1.0f)};
    Vertex v7 = {glm::vec3(1.0f, 3.0f, -2.0f), glm::vec3(0.070f, 0.478f, 0.196f), glm::vec2(1.0f, 1.0f)};
    // bottom of tree
    Vertex v8 = {glm::vec3(-0.2f, 3.0f, -1.4f), glm::vec3(0.278431f, 0.192157f, 0.054902f), glm::vec2(1.0f, 1.0f)};
    Vertex v9 = {glm::vec3(0.2f, 3.0f, -1.4f), glm::vec3(0.278431f, 0.192157f, 0.054902f), glm::vec2(1.0f, 1.0f)};
    Vertex v10 = {glm::vec3(-0.2f, 1.0f, -1.4f), glm::vec3(0.278431f, 0.192157f, 0.054902f), glm::vec2(1.0f, 1.0f)};
    Vertex v11 = {glm::vec3(0.2f, 1.0f, -1.4f), glm::vec3(0.278431f, 0.192157f, 0.054902f), glm::vec2(1.0f, 1.0f)};
    Vertex v12 = {glm::vec3(-0.2f, 3.0f, -0.8f), glm::vec3(0.278431f, 0.192157f, 0.054902f), glm::vec2(1.0f, 1.0f)};
    Vertex v13 = {glm::vec3(-0.2f, 1.0f, -0.8f), glm::vec3(0.278431f, 0.192157f, 0.054902f), glm::vec2(1.0f, 1.0f)};
    Vertex v14 = {glm::vec3(0.2f, 3.0f, -0.8f), glm::vec3(0.278431f, 0.192157f, 0.054902f), glm::vec2(1.0f, 1.0f)};
    Vertex v15 = {glm::vec3(0.2f, 1.0f, -0.8f), glm::vec3(0.278431f, 0.192157f, 0.054902f), glm::vec2(1.0f, 1.0f)};

    std::vector<Vertex> vertices = { v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15 };
    std::vector<unsigned int> indices = {
         // front
		0, 1, 2,
        1, 2, 3,

        // left
        0, 2, 5,
        5, 4, 0,

        // back
        4, 5, 7,
        6, 7, 4,

        // right
        6, 7, 1,
        1, 3, 7,

        // bottom
        2, 3, 5,
        5, 7, 3,

        // top
        0, 1, 4,
        4, 6, 1,

        // bottom of tree
        // front
		8, 9, 10,
        9, 10, 11,

        // left
        8, 10, 13,
        13, 12, 8,

        // back
        12, 13, 15,
        14, 15, 12,

        // right
        14, 15, 9,
        9, 11, 15,

        // bottom
        10, 11, 13,
        13, 15, 11,

        // top
        8, 9, 12,
        12, 14, 9
    };
    std::vector<Texture> textures;

    const Entity tree = reg.create();
    reg.assign<Shader>(
        tree,
        "assets/shader/vertex.glsl",
        "assets/shader/fragment.glsl"
    );
    reg.assign<Renderable>(tree);
    reg.assign<Mesh>(
        tree,
        vertices,
        indices
    );
    reg.assign<Transform>(
        tree,
        position,
        100,
        100,
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.2f, 0.2f, 0.2f)
    );
}
