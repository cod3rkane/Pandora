//
// Created by cod3r on 11/1/19.
//

#include "Constraints.h"

void UI::Constraints::setX(UI::ConstraintsType type) {
    xConstrain = type;
}

void UI::Constraints::setX(UI::ConstraintsType type, int value) {
    xConstrain = type;
    xValue = value;
}

void UI::Constraints::setY(UI::ConstraintsType type) {
    yConstrain = type;
}

void UI::Constraints::setY(UI::ConstraintsType type, int value) {
    yConstrain = type;
    yValue = value;
}

void UI::Constraints::setWidth(UI::ConstraintsType type, int value) {
    widthConstrain = type;
    widthValue = value;
}

void UI::Constraints::setHeight(UI::ConstraintsType type, int value) {
    heightConstrain = type;
    heightValue = value;
}

int UI::Constraints::getX(const int* width = nullptr) {
    switch (xConstrain) {
        case UI::ConstraintsType::CENTER:
            if (width != nullptr) {
                return (Window->getWidth() / 2) - *width;
            } else {
                return Window->getWidth() / 2;
            }

        case UI::ConstraintsType::PERCENTAGE:
            return (Window->getWidth() * xValue) / 100;

        case UI::ConstraintsType::PIXEL:
            return xValue;

        default:
            return 0;
    }
}

int UI::Constraints::getY(const int *height = nullptr) {
    switch (yConstrain) {
        case UI::ConstraintsType::CENTER:
            if (height != nullptr) {
                return (Window->getHeight() / 2) - *height;
            } else {
                return Window->getHeight() / 2;
            }

        case UI::ConstraintsType::PERCENTAGE:
            return (Window->getHeight() * yValue) / 100;

        case UI::ConstraintsType::PIXEL:
            return yValue;

        default:
            return 0;
    }
}

int UI::Constraints::getWidth(int defaultWidth) {
    switch (widthConstrain) {
        case PERCENTAGE:
            return (Window->getWidth() * widthValue) / 100;

        case PIXEL:
            return widthValue;
        case CENTER:
            break;

        default:
            return defaultWidth;
    }
}

int UI::Constraints::getHeight(int defaultHeight) {
    switch (heightConstrain) {
        case UI::ConstraintsType::PERCENTAGE:
            return (Window->getHeight() * heightValue) / 100;

        case UI::ConstraintsType::PIXEL:
            return heightValue;

        default:
            return defaultHeight;
    }
}

float UI::Constraints::getY(float height) {
    switch (yConstrain) {
        case UI::ConstraintsType::CENTER:
            return Window->getHeight() / 2 - height;

        case UI::ConstraintsType::PERCENTAGE:
            return Window->getHeight() * yValue / 100 - height;

        case UI::ConstraintsType::PIXEL:
            return yValue;

        default:
            return 0;
    }
}

float UI::Constraints::getX(float width) {
    switch (xConstrain) {
        case UI::ConstraintsType::CENTER:
            return (Window->getWidth() / 2 - (width / 2) - xValue);

        case UI::ConstraintsType::PERCENTAGE:
            return Window->getWidth() * xValue / 100 - (width / 2);

        case UI::ConstraintsType::PIXEL:
            return xValue;

        default:
            return 0;
    }
}
