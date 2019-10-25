//
// Created by Júlio César Lopes on 02/10/19.
//

#include "render.h"

#include "../components/Shader.h"
#include "../components/Render.h"

#include "../util/files.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../util/stb_image.h"

void System::shader(Registry &reg) {
    const auto view = reg.view<Shader>();

    for (const Entity e : view) {
        // Vertex
        std::string vertexStr = getStringFromFile(view.get(e).vertexPath.c_str());
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexSource = vertexStr.c_str();
        
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);

        // Check Vertex errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR Vertex Shader \n" << infoLog << std::endl;
        }

        // Fragment
        std::string fragmentStr = getStringFromFile(view.get(e).fragmentPath.c_str());
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragmentSource = fragmentStr.c_str();
        
        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
        glCompileShader(fragmentShader);

        // Check Fragment errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR Fragment Shader \n" << infoLog << std::endl;
        }

        // Link shaders
        int* shaderProgram = &view.get(e).program;
        *shaderProgram = glCreateProgram();
        glAttachShader(*shaderProgram, vertexShader);
        glAttachShader(*shaderProgram, fragmentShader);
        glLinkProgram(*shaderProgram);

        // check program errors
        glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
            std::cout << "Error Shader Program \n" << infoLog << std::endl;
        }

        // clean up
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
}

void System::preRender(Registry &reg) {
    const auto view = reg.view<Renderable, Mesh>();

    for (const Entity e : view) {
        unsigned int* VAO = &view.get<Renderable>(e).VAO;
        unsigned int* VBO = &view.get<Renderable>(e).VBO;
        unsigned int* EBO = &view.get<Renderable>(e).EBO;

        if (*VAO == 0) {
            glGenVertexArrays(1, VAO);
            glGenBuffers(1, VBO);
            glGenBuffers(1, EBO);

            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(*VAO);
            glBindBuffer(GL_ARRAY_BUFFER, *VBO);

            std::vector<Vertex> vertices = view.get<Mesh>(e).vertices;
            std::vector<unsigned int> indices = view.get<Mesh>(e).indices;

            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

            // Vertex positions
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            glEnableVertexAttribArray(0);

            // Vertex colors
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Colors));
            glEnableVertexAttribArray(1);

            // Vertex textures
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
            glEnableVertexAttribArray(2);

            glBindVertexArray(0);
        }
    }
}

void System::render(Registry &reg, float deltaTime, int windowWidth, int windowHeight) {
    const auto view = reg.view<Shader, Renderable, Mesh>();
    for (const Entity e : view) {
        glUseProgram(view.get<Shader>(e).program);
        glBindVertexArray(view.get<Renderable>(e).VAO);

        glDrawElements(GL_TRIANGLES, view.get<Mesh>(e).indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void System::cleanRender(Registry &reg) {
    const auto view = reg.view<Renderable>();
    for (const Entity e : view) {
        glDeleteVertexArrays(1, &view.get(e).VAO);
        glDeleteBuffers(1, &view.get(e).VBO);
        glDeleteBuffers(1, &view.get(e).EBO);
    }
}
