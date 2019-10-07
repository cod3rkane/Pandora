#ifndef CGAME_INTERACTIONS_H
#define CGAME_INTERACTIONS_H

#include <GLFW/glfw3.h>

#include "../util/registry.h"

namespace System {
    void userInputs(Registry &reg, GLFWwindow* mainWindow, float deltaTime);
}

#endif // CGAME_INTERACTIONS_H
