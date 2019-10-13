//
// Created by Júlio César Lopes on 05/10/19.
//

#include "transformations.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <entt/entt.hpp>
#include "../components/Shader.h"
#include "../components/Transform.h"
#include "../util/Camera.h"

void System::transformations(Registry &reg, float deltaTime, int windowWidth, int windowHeight) {
    Camera camera = entt::service_locator<Camera>::ref();

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

        glUseProgram(view.get<Shader>(e).program);

        glUniformMatrix4fv(glGetUniformLocation(view.get<Shader>(e).program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(view.get<Shader>(e).program, "view"), 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(view.get<Shader>(e).program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    }
}

void System::transformations2D(Registry &reg, float deltaTime, int windowWidth, int windowHeight) {
    const auto view = reg.view<Shader, Transform2D>();
    for (const Entity e : view) {
        glm::mat4 model = glm::mat4(1.0f);

        glm::vec3 rotation = view.get<Transform2D>(e).Rotation;
        // resize GUI
        float xScale = view.get<Transform2D>(e).width / windowWidth;
        float yScale = view.get<Transform2D>(e).height / windowHeight;

        glm::vec2 position = view.get<Transform2D>(e).Position;
        float xOffset = (position.x / windowWidth) * 2.0f -1.0f;
        float yOffset = (position.y / windowHeight) * 2.0f -1.0f;

        // @TODO: dummy logic, fix that later
        if (xOffset < 0) {
            xOffset += xScale;
        } else {
            xOffset -= xScale;
        }

        if (yOffset < 0) {
            yOffset += yScale;
        } else {
            yOffset -= yScale;
        }

        float inverseYOffset = yOffset * -1.0f;

        model = glm::translate(model, glm::vec3(xOffset, inverseYOffset, 0.0f));
        model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

        glUseProgram(view.get<Shader>(e).program);

        if (rotation.x == 0.0f && rotation.y == 0.0f && rotation.z == 0.0f) {
            glUniform2f(glGetUniformLocation(view.get<Shader>(e).program, "scale"), xScale, yScale);
        } else {
            glUniform2f(glGetUniformLocation(view.get<Shader>(e).program, "scale"), xScale, xScale);
        }
        glUniformMatrix4fv(glGetUniformLocation(view.get<Shader>(e).program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    }
}
