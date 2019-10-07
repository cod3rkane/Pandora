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

void Game::init(GLFWwindow* window) {
    window = window;
    // init entities
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    const Entity e = reg.create();
    reg.assign<Shader>(
        e,
        "assets/shader/vertex-texture2d.glsl",
        "assets/shader/fragment-texture2d.glsl",
        "assets/textures/wall.jpg",
        vertices,
        sizeof(vertices),
        indices,
        sizeof(indices)
    );
    reg.assign<Transform>(
        e,
        glm::vec3(0.0f, 0.0f, -3.0f),
        100,
        100,
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );
    reg.assign<Renderable>(e);

    float verticesCube[] = {
        // front
        -1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
        1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
        1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
        // back
        -1.0f, -1.0f, -1.0f,   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
        1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f
    };
    unsigned int indicesCube[] = {
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

    const Entity e2 = reg.create();
    reg.assign<Shader>(
        e2,
        "assets/shader/vertex-texture2d.glsl",
        "assets/shader/fragment-texture2d.glsl",
        nullptr,
        verticesCube,
        sizeof(verticesCube),
        indicesCube,
        sizeof(indicesCube)
    );
    reg.assign<Transform>(
        e2,
        glm::vec3(1.0f, 0.0f, -3.0f),
        100,
        100,
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.2f, 0.2f, 0.2f)
    );
    reg.assign<Renderable>(e2);

    System::shader(reg);
}

void Game::update(float deltaTime, int windowWidth, int windowHeight) {
    // get inputs
    // create world

    System::userInputs(reg, deltaTime);
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
