//
// Created by Júlio César Lopes on 02/10/19.
//

#ifndef CGAME_SHADER_H
#define CGAME_SHADER_H

#include <GL/glew.h>

struct Shader {
    const char* filePathShader;
    const char* filePathVertex;
    const char* texturePath;
    const float* vertices;
    unsigned long verticesSize;
    const unsigned int* indices;
    unsigned long indicesSize;
    const char* vertexShaderSource;
    int vertexShader;
    const char* fragmentShaderSource;
    int fragmentShader;
    int shaderProgram;
    unsigned int texture;
};

#endif //CGAME_SHADER_H
