#include <iostream>
#include "core/Application.h"

int main() {
    std::cout << "Hello, cgame" << std::endl;
    Application application;

    application.init();
    application.update();
    application.start();

    return 0;
}