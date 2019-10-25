#include "Shader.h"

#include "../util/files.h"

Core::Shader::Shader() {};

Core::Shader::Shader(std::string vertexPath, std::string fragmentPath) {
    // Vertex
    std::string vertexStr = getStringFromFile(vertexPath.c_str());
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSource = vertexStr.c_str();
    
    glShaderSource(vertexShaderID, 1, &vertexSource, NULL);
    glCompileShader(vertexShaderID);

    // Check Vertex errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
        std::cout << "ERROR Vertex Shader \n" << infoLog << std::endl;
    }

    // Fragment
    std::string fragmentStr = getStringFromFile(fragmentPath.c_str());
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSource = fragmentStr.c_str();
    
    glShaderSource(fragmentShaderID, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShaderID);

    // Check Fragment errors
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
        std::cout << "ERROR Fragment Shader \n" << infoLog << std::endl;
    }

    // Link shaders
    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // check program errors
    glGetProgramiv(programID, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << "Error Shader Program \n" << infoLog << std::endl;
    }
}

void Core::Shader::bind() {
    glUseProgram(programID);
}

void Core::Shader::unbind() {
    glUseProgram(0);
}

void Core::Shader::cleanUp() {
    unbind();
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glDeleteProgram(programID);
}

GLuint Core::Shader::getProgramID() {
    return programID;
}
