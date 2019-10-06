//
// Created by Júlio César Lopes on 05/10/19.
//

#include "transformations.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../components/Shader.h"
#include "../components/Transform.h"

void System::transformations(Registry &reg, int windowWidth, int windowHeight, glm::mat4 cameraView) {
    const auto view = reg.view<Shader, Transform>();

    for (const Entity e : view) {
        // create transformations
        glm::mat4 viewTransformation = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);

        glm::vec3 rotation = view.get<Transform>(e).rotation;

        projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / windowHeight, 0.1f, 100.0f);
        model = glm::translate(model, view.get<Transform>(e).position);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, view.get<Transform>(e).scale);

        glUseProgram(view.get<Shader>(e).shaderProgram);

        glUniformMatrix4fv(glGetUniformLocation(view.get<Shader>(e).shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(view.get<Shader>(e).shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(cameraView));
        glUniformMatrix4fv(glGetUniformLocation(view.get<Shader>(e).shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    }
}
