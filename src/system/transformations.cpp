//
// Created by Júlio César Lopes on 05/10/19.
//

#include "transformations.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../components/Shader.h"
#include "../components/Transform.h"

void System::transformations(Registry &reg, int windowWidth, int windowHeight) {
    const auto view = reg.view<Shader, Transform>();

    for (const Entity e : view) {
        // create transformations
        glm::mat4 viewTransformation = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);

        float angle = 0.0f;

        projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / windowHeight, 0.1f, 100.0f);
        viewTransformation = glm::translate(viewTransformation, view.get<Transform>(e).position);
        model = glm::scale(model, view.get<Transform>(e).scale);
        model = glm::rotate(model, glm::radians(angle), view.get<Transform>(e).rotation);

        glUseProgram(view.get<Shader>(e).shaderProgram);

        glUniformMatrix4fv(glGetUniformLocation(view.get<Shader>(e).shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(view.get<Shader>(e).shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(viewTransformation));
        glUniformMatrix4fv(glGetUniformLocation(view.get<Shader>(e).shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    }
}
