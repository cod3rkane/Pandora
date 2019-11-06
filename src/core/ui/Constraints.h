//
// Created by cod3r on 11/1/19.
//

#ifndef CGAME_CONSTRAINTS_H
#define CGAME_CONSTRAINTS_H

#include <iostream>
#include <entt/entt.hpp>

#include "../Window.h"

namespace UI {
    enum ConstraintsType {
        CENTER,
        PIXEL,
        PERCENTAGE,
    };

    class Constraints {
        ConstraintsType xConstrain;
        int xValue;
        ConstraintsType yConstrain;
        int yValue;
        ConstraintsType widthConstrain;
        int widthValue;
        ConstraintsType heightConstrain;
        int heightValue;
        Core::Window* Window = &entt::service_locator<Core::Window>::ref();
    public:
        void setX(ConstraintsType type);
        void setX(ConstraintsType type, int value);
        void setY(ConstraintsType type);
        void setY(ConstraintsType type, int value);
        void setWidth(ConstraintsType type, int value);
        void setHeight(ConstraintsType type, int value);

        int getX(const int* width);
        float getX(float width);
        int getY(const int* height);
        float getY(float height);
        int getWidth(int defaultWidth);
        int getHeight(int defaultHeight);
    };
}


#endif //CGAME_CONSTRAINTS_H
