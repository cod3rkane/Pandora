//
// Created by Júlio César Lopes on 02/10/19.
//

#include "Game.h"
#include <glm/glm.hpp>
#include "../system/render.h"
#include "../system/transformations.h"
#include "../components/Shader.h"
#include "../components/Render.h"
#include "../components/Transform.h"

Game::Game() {

}

Game::~Game() {

}

void Game::init() {
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

    const Entity e2 = reg.create();
    reg.assign<Shader>(
        e2,
        "assets/shader/vertex-texture2d.glsl",
        "assets/shader/fragment-texture2d.glsl",
        "assets/textures/vegetta.jpg",
        vertices,
        sizeof(vertices),
        indices,
        sizeof(indices)
    );
    reg.assign<Transform>(
        e2,
        glm::vec3(1.0f, 1.0f, -3.0f),
        100,
        100,
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );
    reg.assign<Renderable>(e2);

    System::shader(reg);
}

void Game::update(int windowWidth, int windowHeight) {
    // get inputs
    // create world
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
