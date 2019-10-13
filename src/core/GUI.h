#ifndef CGAME_GUI_H
#define CGAME_GUI_H

#include <iostream>
#include <glm/vec2.hpp>

#include "../util/registry.h"
#include "../components/Render.h"
#include "../components/Shader.h"
#include "../components/Transform.h"

class GUI {
public:
    void create(Registry &reg);
};

#endif
