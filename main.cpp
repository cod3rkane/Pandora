#include <iostream>
#include "src/core/Application.h"

int main() {
    Application application;

    application.init();
    application.update();
    application.start();

    return 0;
}