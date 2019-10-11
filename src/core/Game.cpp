//
// Created by Júlio César Lopes on 02/10/19.
//

#include "Game.h"

#include <entt/entt.hpp>

#include "../system/render.h"
#include "../system/transformations.h"
#include "../system/interactions.h"
#include "../components/Shader.h"
#include "../components/Render.h"
#include "../components/Transform.h"
#include "../util/Camera.h"

Game::Game() {
    Camera playerCamera(glm::vec3(0.0f, 0.0f, 3.0f));
    entt::service_locator<Camera>::set(playerCamera);
}

Game::~Game() {

}

void Game::init(GLFWwindow* mainWindow) {
    window = mainWindow;

    Vertex v0 = {glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.2f, 0.1f), glm::vec2(1.0f, 1.0f)};
    Vertex v1 = {glm::vec3(1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.2f, 0.4f), glm::vec2(1.0f, 1.0f)};
    Vertex v2 = {glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 0.2f, 0.3f), glm::vec2(1.0f, 1.0f)};
    Vertex v3 = {glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 0.2f, 0.2f), glm::vec2(1.0f, 1.0f)};
    Vertex v4 = {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.2f, 0.3f), glm::vec2(1.0f, 1.0f)};
    Vertex v5 = {glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.2f, 0.1f), glm::vec2(1.0f, 1.0f)};
    Vertex v6 = {glm::vec3(1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 0.2f, 0.2f), glm::vec2(1.0f, 1.0f)};
    Vertex v7 = {glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 0.2f, 0.3f), glm::vec2(1.0f, 1.0f)};
    std::vector<Vertex> vertices = { v0, v1, v2, v3, v4, v5, v6, v7 };
    std::vector<unsigned int> indices = {
         // front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
    };
    std::vector<Texture> textures;

    const Entity e2 = reg.create();
    reg.assign<Shader>(
        e2,
        "assets/shader/vertex.glsl",
        "assets/shader/fragment.glsl"
    );
    reg.assign<Renderable>(e2);
    reg.assign<Mesh>(
        e2,
        vertices,
        indices
    );
    reg.assign<Transform>(
        e2,
        glm::vec3(1.0f, 0.0f, -3.0f),
        100,
        100,
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.2f, 0.2f, 0.2f)
    );

    System::shader(reg);
    System::preRender(reg);
}

void Game::update(float deltaTime, int windowWidth, int windowHeight) {
    // get inputs
    // create world

    System::userInputs(reg, window, deltaTime);
    System::transformations(reg, windowWidth, windowHeight);
}

void Game::start() {
    // game loop
    // render things
    // Load Systems
    System::render(reg);
}

void Game::clean() {
    System::cleanRender(reg);
}
