//
// Created by Júlio César Lopes on 05/10/19.
//

#ifndef CGAME_TRANSFORM_H
#define CGAME_TRANSFORM_H

#include <glm/vec3.hpp>

struct Transform {
    glm::vec3 position;
    int width;
    int height;
    glm::vec3 rotation;
    glm::vec3 scale;;
};

#endif //CGAME_TRANSFORM_H
