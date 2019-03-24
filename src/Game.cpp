#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include "core/sol.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "core/StbImage.h"

std::string loadFile(const GLchar* path) {
  std::ifstream stream(path, std::ios::binary);
  std::stringstream strStream;

  strStream << stream.rdbuf();

  stream.close();

  std::string str = strStream.str();
  
  return str.c_str();
}

void checkCompileErrors(GLuint shader, std::string type) {
  GLint success;
  GLchar infoLog[1024];
  if(type != "PROGRAM")
  {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if(!success)
      {
          glGetShaderInfoLog(shader, 1024, NULL, infoLog);
          std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
      }
  }
  else
  {
      glGetProgramiv(shader, GL_LINK_STATUS, &success);
      if(!success)
      {
          glGetProgramInfoLog(shader, 1024, NULL, infoLog);
          std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
      }
  }
}

int main() {
  sol::state lua;
  lua.open_libraries();

  lua.script_file("src/scripts/window.lua");

  std::string windowTitle = lua["window"]["title"];
  int windowWidth = lua["window"]["width"];
  int windowHeight = lua["window"]["height"];

  // check lua script errors

  if (SDL_Init(SDL_INIT_EVERYTHING) > 0) {
    std::cout << "ERROR: could not start SDL2" << std::endl;

    return -1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_Window* window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL |     SDL_WINDOW_SHOWN);

  if (!window) {
    std::cout << "ERROR: could not open window with SDL2" << SDL_GetError() << std::endl;

    return -1;
  }

  SDL_GLContext context = SDL_GL_CreateContext(window);

  if( context == NULL ) {
    std::cout << "OpenGL context could not be created! SDL Error" << SDL_GetError() << std::endl;

    return -1;
  }

  // start glew
  glewExperimental = GL_TRUE;
  glewInit();

  //Use Vsync
  if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
    std::cout << "Warning: Unable to set VSync! SDL Error:" << SDL_GetError() << std::endl;

    return -1;
  }

  // tell GLto only draw onto a pixel if the shape is closer to the view.
  // glEnable(GL_DEPTH_TEST);
  // glDepthFunc(GL_LESS);

  GLfloat vertices[] = {
    // positions          // colors           // texture coords
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
  };

  GLuint indices[] = {
    0, 1, 3, // First triangle
    1, 2, 3 // Second triangle
  };

  // We will copy chunk of memory onto the graphicscard in a unit called a vertex buffer object (VBO)
  // To do this we "generate" an empty buffer, set it as the current buffr in OpenGL's state machine by "binding"
  // Then copy the points into the currently bound buffer.

  // When we want to draw, all we do then is bind the VAO and draw.
  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // Compile Shaders
  std::string vertexCode = loadFile("src/shaders/simple_vert.glsl");
  std::string fragmentCode = loadFile("src/shaders/simple_frag.glsl");

  const GLchar* vCode = vertexCode.c_str();
  const GLchar* fCode = fragmentCode.c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vCode, NULL);
  glCompileShader(vertexShader);
  checkCompileErrors(vertexShader, "VERTEX");

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fCode, NULL);
  glCompileShader(fragmentShader);
  checkCompileErrors(fragmentShader, "FRAGMENT");

  // Linking Shaders together
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // load and generate the texture
  int width, height, nrChannels;
  unsigned char* data = stbi_load("src/assets/container.jpg", &width, &height, &nrChannels, 0);
  if (data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
  } else {
      std::cout << "Failed to load texture" << std::endl;
  }

  stbi_image_free(data);

  glUseProgram(shaderProgram);
  glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

  bool quit = false;
  SDL_Event sdlEvent;

  //Enable text input
  // SDL_StartTextInput();

  while (!quit) {
    while (SDL_PollEvent(&sdlEvent) != 0) {
      if (sdlEvent.type == SDL_QUIT) {
        quit = true;
      }
    }
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, 6);

    //Unbind program
		glUseProgram( NULL );
    SDL_GL_SwapWindow(window);
  }

  // Delete Buffers
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  // SDL_StopTextInput();
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
