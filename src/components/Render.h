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
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
};

#endif //CGAME_RENDERABLE_H
