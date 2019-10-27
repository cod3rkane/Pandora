//
// Created by Júlio César Lopes on 02/10/19.
//

#include "Application.h"

Application::Application() {

}

Application::~Application() {

}

void Application::init() {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
}

void Application::update() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        glfwTerminate();
        std::cout << "GLEW Error" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Application::start() {
    game.init(window, windowWidth, windowHeight);

    while (!glfwWindowShouldClose(window)) {
        // per-frame time lofic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

        glMatrixMode(GL_PROJECTION);
        glViewport(0, 0, windowWidth, windowHeight);
        glMatrixMode(GL_MODELVIEW);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);

        game.update(deltaTime, windowWidth, windowHeight);

        game.start(deltaTime, windowWidth, windowHeight);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    game.clean();

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
