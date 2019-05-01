#include "app.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core {
  void setupGLFW() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  }

  GLFWwindow* createWindow() {
    GLFWwindow* window = glfwCreateWindow(1280, 720, "SEWR - Game", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (window == NULL) {
      printf("Failed to create GLFW Window\n");
      glfwTerminate();

      return NULL;
    }

    return window;
  }

  void setupGL() {
    if (!gladLoadGL()) {
      printf("Failed to initialize OpenGl context");
    }

    glViewport(0, 0, 1280, 720);
  }

  void runGame() {
    setupGLFW();
    GLFWwindow* window = createWindow();
    setupGL();

    // Game Loop
    while (!glfwWindowShouldClose(window)) {
      // check if any events have been activated
      glfwPollEvents();

      // render
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // swap
      glfwSwapBuffers(window);
    }
  }
}
