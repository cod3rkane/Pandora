//
// Created by Júlio César Lopes on 02/10/19.
//

#ifndef CGAME_SHADER_H
#define CGAME_SHADER_H

struct Shader {
    const char* filePathShader;
    const char* filePathVertex;
    const char* vertexShaderSource;
    int vertexShader;
    const char* fragmentShaderSource;
    int fragmentShader;
    int shaderProgram;
};

#endif //CGAME_SHADER_H
