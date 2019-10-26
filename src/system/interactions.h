#ifndef CGAME_INTERACTIONS_H
#define CGAME_INTERACTIONS_H

#include <GLFW/glfw3.h>
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../util/registry.h"
#include "../util/Camera.h"
#include "../core/Window.h"

namespace System {
    void userInputs(Registry &reg, float deltaTime);
}

#endif // CGAME_INTERACTIONS_H
