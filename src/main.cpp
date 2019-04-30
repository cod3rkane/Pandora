#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const int WIDTH = 1280, HEIGHT = 720;

int main(int, char *[]) {
  printf("Hello C \n");
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Create a Window
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "SEWR - Spatial Explorer Game With Resouces", NULL, NULL);
  glfwMakeContextCurrent(window);

  if (window == NULL) {
    printf("Failed to create GLFW Window\n");
    glfwTerminate();

    return EXIT_FAILURE;
  }

  if (!gladLoadGL()) {
    printf("Failed to initialize OpenGl context");

    return EXIT_FAILURE;
  }

  glViewport(0, 0, WIDTH, HEIGHT);

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

  glfwTerminate();

  return EXIT_SUCCESS;
}

