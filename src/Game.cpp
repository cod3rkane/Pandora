#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;

std::string loadFile(const GLchar* path) {
  std::ifstream stream(path, std::ios::binary);
  std::stringstream strStream;

  strStream << stream.rdbuf();

  stream.close();

  std::string str = strStream.str();
  
  return str.c_str();
}

int main() {
  if (!glfwInit()) {
    std::cout << "ERROR: could not start GLFW3" << std::endl;

    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pandora", NULL, NULL);

  if (!window) {
    std::cout << "ERROR: could not open window with GLFW" << std::endl;
    glfwTerminate();

    return 1;
  }

  glfwMakeContextCurrent(window);

  // start glew
  glewExperimental = GL_TRUE;
  glewInit();

  // tell GLto only draw onto a pixel if the shape is closer to the view.
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  GLfloat points[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
  };

  // We will copy chunk of memory onto the graphicscard in a unit called a vertex buffer object (VBO)
  // To do this we "generate" an empty buffer, set it as the current buffr in OpenGL's state machine by "binding"
  // Then copy the points into the currently bound buffer.

  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

  // Wehn we want to draw, all we do then is bind the VAO and draw.
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  // Compile Shaders
  std::string vertexCode = loadFile("src/shaders/simple_vert.glsl");
  std::string fragmentCode = loadFile("src/shaders/simple_frag.glsl");

  const GLchar *vCode = vertexCode.c_str();
  const GLchar *fCode = fragmentCode.c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vCode, NULL);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fCode, NULL);
  glCompileShader(fragmentShader);

  // Linking Shaders together
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, fragmentShader);
  glAttachShader(shaderProgram, vertexShader);
  glLinkProgram(shaderProgram);

  while(!glfwWindowShouldClose(window)) {
    // wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    // draw points 0-3
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwPollEvents();
    glfwSwapBuffers(window); // put the stuff we've been drawing onto the display
  }

  glfwTerminate();
  return 0;
}
