//
// Created by cod3r on 11/10/19.
//

#ifndef CGAME_MAINMENU_H
#define CGAME_MAINMENU_H

#include <glm/vec4.hpp>

#include "../core/ui/UIComponent.h"
#include "../core/ui/Button.h"
#include "../core/UIManager.h"
#include "../core/ui/Constraints.h"
#include "../core/game-state/GameState.h"

namespace GUI {
    class MainMenu {
        UIManager* uiManager;
        GameStateTypes* gameState;
        UI::CoreComponent* bgComponent = new UI::Component();
        UI::CoreComponent* newGameBtn = new UI::Button();
        UI::CoreComponent* savedGameBtn = new UI::Button();
        UI::CoreComponent* exitGameBtn = new UI::Button();
    public:
        MainMenu();
        explicit MainMenu(UIManager* manager);
        ~MainMenu();
        void init(UIManager& manager, GameStateTypes* state);
        void update();
        void render();
        void clean();
    };
}

#endif //CGAME_MAINMENU_H
