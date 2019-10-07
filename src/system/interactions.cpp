#include "interactions.h"

#include <entt/entt.hpp>
#include <GLFW/glfw3.h>

#include "../util/Camera.h"

void System::userInputs(Registry &reg, float deltaTime) {
    Camera* camera = &entt::service_locator<Camera>::ref();
    camera->Position += camera->Front * 2.5f * deltaTime;
}
