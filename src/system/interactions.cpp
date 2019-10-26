#include "interactions.h"

bool firstMouse = true;
double lastMouseX;
double lastMouseY;

void System::userInputs(Registry &reg, float deltaTime) {
    Core::Window* Window = &entt::service_locator<Core::Window>::ref();
    if (glfwGetKey(Window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        // @TODO: change this...
        glfwSetWindowShouldClose(Window->getWindow(), true);
    }

    Camera* camera = &entt::service_locator<Camera>::ref();
    float cameraSpeed = 2.5f * deltaTime;
    // Camera Actions
    if (glfwGetKey(Window->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        camera->Position += cameraSpeed * camera->Front;
    }

    if (glfwGetKey(Window->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        camera->Position -= cameraSpeed * camera->Front;
    }

    if (glfwGetKey(Window->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        camera->Position -= glm::normalize(glm::cross(camera->Front, camera->Up)) * cameraSpeed;
    }
    
    if (glfwGetKey(Window->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        camera->Position += glm::normalize(glm::cross(camera->Front, camera->Up)) * cameraSpeed;
    }

    double mouseX, mouseY;
    glfwGetCursorPos(Window->getWindow(), &mouseX, &mouseY);
    int mouseLeftBtn = glfwGetMouseButton(Window->getWindow(), GLFW_MOUSE_BUTTON_RIGHT);
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
