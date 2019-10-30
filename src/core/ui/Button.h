#ifndef CGAME_UIBUTTON_H
#define CGAME_UIBUTTON_H

#include <iostream>

#include "CoreComponent.h"

namespace UI {
    class Button : public UI::CoreComponent {
    public:
        Button(): UI::CoreComponent::CoreComponent() {
            UI::CoreComponent::setInteractive(true);
        }
        void update() override;
        void update(double mouseX, double mouseY, bool isMousePressed) override;
    };
}

#endif // CGAME_UIBUTTON_H
