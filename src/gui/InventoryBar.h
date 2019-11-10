//
// Created by cod3r on 11/10/19.
//

#ifndef CGAME_INVENTORYBAR_H
#define CGAME_INVENTORYBAR_H

#include <glm/vec4.hpp>

#include "../core/ui/UIComponent.h"
#include "../core/ui/Button.h"
#include "../core/UIManager.h"
#include "../core/ui/Constraints.h"
#include "../core/game-state/GameState.h"

namespace GUI {
    class InventoryBar {
        UIManager* uiManager;
        UI::CoreComponent* button1 = new UI::Button();
        UI::CoreComponent* button2 = new UI::Button();
        UI::CoreComponent* button3 = new UI::Button();
        bool hasCreated = false;
    public:
        InventoryBar();
        ~InventoryBar();
        void init(UIManager& manager);
        void update();
        void render();
        void clean();
    };
}

#endif //CGAME_INVENTORYBAR_H
