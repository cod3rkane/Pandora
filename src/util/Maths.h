#ifndef CGAME_MATHS_H
#define CGAME_MATHS_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Maths {
public:
    static glm::mat4 createTransformationMatrix(glm::vec3 Position, glm::vec3 Scale, glm::vec3 Rotation) {
        glm::mat4 matrix = glm::mat4(1.0f);

        matrix = glm::translate(matrix, Position);
        matrix = glm::rotate(matrix, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        matrix = glm::rotate(matrix, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        matrix = glm::rotate(matrix, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        matrix = glm::scale(matrix, Scale);

        return matrix;
    }
};

#endif // CGAME_MATHS_H
