#include "interactions.h"

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../util/Camera.h"

void System::userInputs(Registry &reg, GLFWwindow* mainWindow, float deltaTime) {
    if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        // @TODO: change this...
        glfwSetWindowShouldClose(mainWindow, true);
    }

    Camera* camera = &entt::service_locator<Camera>::ref();
    float cameraSpeed = 2.5f * deltaTime;
    // Camera Actions
    if (glfwGetKey(mainWindow, GLFW_KEY_W) == GLFW_PRESS) {
        camera->Position += cameraSpeed * camera->Front;
    }
    if (glfwGetKey(mainWindow, GLFW_KEY_S) == GLFW_PRESS) {
        camera->Position -= cameraSpeed * camera->Front;
    }
    if (glfwGetKey(mainWindow, GLFW_KEY_A) == GLFW_PRESS) {
        camera->Position -= glm::normalize(glm::cross(camera->Front, camera->Up)) * cameraSpeed;
    }
    if (glfwGetKey(mainWindow, GLFW_KEY_D) == GLFW_PRESS) {
        camera->Position += glm::normalize(glm::cross(camera->Front, camera->Up)) * cameraSpeed;
    }
}
