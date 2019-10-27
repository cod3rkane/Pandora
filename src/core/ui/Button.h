#ifndef CGAME_UIBUTTON_H
#define CGAME_UIBUTTON_H

#include <iostream>

#include "UIComponent.h"

namespace UI {
    class Button : public UI::Component {
    public:
        Button() : UI::Component() {
            isInteractive = true;
        }
    };
}

#endif // CGAME_UIBUTTON_H
