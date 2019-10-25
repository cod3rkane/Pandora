#ifndef CGAME_CORE_SHADER_H
#define CGAME_CORE_SHADER_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Core {
    class Shader {
        GLuint programID;
        GLuint vertexShaderID = 0;
        GLuint fragmentShaderID = 0;
    public:
        Shader();
        Shader(std::string vertexPath, std::string fragmentPath);
        void bind();
        void unbind();
        void cleanUp();

        GLuint getProgramID();

        // @TODO: bind attributes
    };
}

#endif // CGAME_CORE_SHADER_H
