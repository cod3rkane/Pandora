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

        glm::vec2 rotation = view.get<Transform2D>(e).Rotation;

        model = glm::translate(model, glm::vec3(view.get<Transform2D>(e).Position, 0.0f));
        model = glm::rotate(model, view.get<Transform2D>(e).Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, view.get<Transform2D>(e).Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, view.get<Transform2D>(e).Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

        glUseProgram(view.get<Shader>(e).program);

        // resize GUI
        float xScale = view.get<Transform2D>(e).width / windowWidth;
        float yScale = view.get<Transform2D>(e).height / windowHeight;
        // @TODO if it's rotation is better to use xScale x xScale, otherwise yScale instead.
        glUniform2f(glGetUniformLocation(view.get<Shader>(e).program, "scale"), xScale, xScale);
        glUniformMatrix4fv(glGetUniformLocation(view.get<Shader>(e).program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    }
}
