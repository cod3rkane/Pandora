//
// Created by Júlio César Lopes on 02/10/19.
//

#include "render.h"
#include <iostream>
#include <GL/glew.h>
#include "../components/Shader.h"
#include "../components/Render.h"
#include "../util/files.h"

void System::shader(Registry &reg) {
    const auto view = reg.view<Shader, Renderable>();
    for (const Entity e : view) {
        // Vertex
        const char* vertexShaderSource = view.get<Shader>(e).vertexShaderSource;
        vertexShaderSource = getStringFromFile("../assets/shader/vertex.glsl").c_str();
        int* vertexShader = &view.get<Shader>(e).vertexShader;

        *vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(*vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(*vertexShader);

        // Check Vertex errors
        int success;
        char infoLog[512];
        glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(*vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR Vertex Shader \n" << infoLog << std::endl;
        }

        // Fragment
        const char* fragmentShaderSource = view.get<Shader>(e).fragmentShaderSource;
        fragmentShaderSource = getStringFromFile("../assets/shader/fragment.glsl").c_str();
        int* fragmentShader = &view.get<Shader>(e).fragmentShader;

        *fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(*fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(*fragmentShader);

        // Check Fragment errors
        glGetShaderiv(*fragmentShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(*fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR Fragment Shader \n" << infoLog << std::endl;
        }

        // Link shaders
        int* shaderProgram = &view.get<Shader>(e).shaderProgram;
        *shaderProgram = glCreateProgram();
        glAttachShader(*shaderProgram, *vertexShader);
        glAttachShader(*shaderProgram, *fragmentShader);
        glLinkProgram(*shaderProgram);

        // check program errors
        glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
            std::cout << "Error Shader Program \n" << infoLog << std::endl;
        }

        // clean up
        glDeleteShader(*vertexShader);
        glDeleteShader(*fragmentShader);

        // @TODO: get vertices from some component
        float vertices[] = {
                -0.5f, 0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                0.0f, -0.5f, 0.0f
        };
        // @TODO: get indices from some component
        unsigned int indices[] = {
                0, 1, 2
        };

        unsigned int* VAO = &view.get<Renderable>(e).VAO;
        unsigned int* VBO = &view.get<Renderable>(e).VBO;
        unsigned int* EBO = &view.get<Renderable>(e).EBO;

        glGenVertexArrays(1, VAO);
        glGenBuffers(1, VBO);
        glGenBuffers(1, EBO);

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(*VAO);

        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); // (void*)0 instead of nullptr
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's
        // bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
    }
}

void System::render(Registry &reg) {
    const auto view = reg.view<Shader, Renderable>();
    for (const Entity e : view) {
        glUseProgram(view.get<Shader>(e).shaderProgram);
        glBindVertexArray(view.get<Renderable>(e).VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }
}

void System::cleanRender(Registry &reg) {
    const auto view = reg.view<Shader, Renderable>();
    for (const Entity e : view) {
        glDeleteVertexArrays(1, &view.get<Renderable>(e).VAO);
        glDeleteBuffers(1, &view.get<Renderable>(e).VBO);
        glDeleteBuffers(1, &view.get<Renderable>(e).EBO);
    }
}
