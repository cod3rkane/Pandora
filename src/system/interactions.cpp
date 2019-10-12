#include "interactions.h"

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../util/Camera.h"

bool firstMouse = true;
double lastMouseX;
double lastMouseY;

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

    double mouseX, mouseY;
    glfwGetCursorPos(mainWindow, &mouseX, &mouseY);
    int mouseLeftBtn = glfwGetMouseButton(mainWindow, GLFW_MOUSE_BUTTON_RIGHT);
    if (mouseLeftBtn == GLFW_PRESS) {
        if (firstMouse) {
            lastMouseX = mouseX;
            lastMouseY = mouseY;
            firstMouse = false;
        }

        float xoffset = mouseX - lastMouseX;
        float yoffset = lastMouseY - mouseY;
        camera->mouseMovement(xoffset, yoffset);
    }

    lastMouseX = mouseX;
    lastMouseY = mouseY;
}
