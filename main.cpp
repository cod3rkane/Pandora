#include <iostream>
#include "src/core/Application.h"

int main() {
    std::cout << "Hello, cgame" << std::endl;
    Application application;

    application.init();
    application.update();
    application.start();

    return 0;
}