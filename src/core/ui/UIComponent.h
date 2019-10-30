#ifndef CGAME_UICOMPONENT_H
#define CGAME_UICOMPONENT_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>

#include "../../util/registry.h"
#include "../../components/Shader.h"
#include "../../components/Transform.h"
#include "../../components/Render.h"
#include "../../util/Maths.h"
#include "CoreComponent.h"

namespace UI {
    class Component : public UI::CoreComponent {
    public:
        void update() override;
    };
}

#endif // CGAME_UICOMPONENT_H
