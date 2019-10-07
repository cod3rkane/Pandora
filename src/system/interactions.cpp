#include "interactions.h"

#include "../util/Camera.h"
#include <entt/entt.hpp>

void System::userInputs(Registry &reg, float deltaTime) {
    Camera* camera = &entt::service_locator<Camera>::ref();
    camera->Position += camera->Front * 2.5f * deltaTime;
}
