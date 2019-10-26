#include "Window.h"

void Core::Window::setWindow(GLFWwindow* window) {
    mainWindow = window;
}

GLFWwindow* Core::Window::getWindow() {
    return mainWindow;
}

void Core::Window::setWidth(int w) {
    width = w;
}

int Core::Window::getWidth() {
    return width;
}

void Core::Window::setHeight(int h) {
    height = h;
}

int Core::Window::getHeight() {
    return height;
}
