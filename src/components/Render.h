//
// Created by Júlio César Lopes on 02/10/19.
//

#ifndef CGAME_RENDERABLE_H
#define CGAME_RENDERABLE_H

#include <iostream>
#include <glm/ext.hpp>

struct Renderable {
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
};

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Colors;
    glm::vec2 TexCoords;
};

struct Vertex2D {
    glm::vec2 Positions;
    glm::vec3 Colors;
    // glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
};

struct Mesh2D {
    std::vector<Vertex2D> vertices;
    // std::vector<unsigned int> indices;
    // std::vector<Texture> textures;
};

#endif //CGAME_RENDERABLE_H
