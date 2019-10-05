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
    const Entity e = reg.create();

    reg.assign<Shader>(e, "../assets/shader/vertex-texture2d.glsl", "../assets/shader/fragment-texture2d.glsl", "../assets/textures/wall.jpg");
    reg.assign<Transform>(
        e,
        glm::vec3(0.0f, 0.0f, -3.0f),
        100,
        100,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );
    reg.assign<Renderable>(e);

    System::shader(reg);
}

void Game::update() {
    // get inputs
    // create world
}

void Game::start() {
    // game loop
    // render things
    // Load Systems
    System::transformations(reg);
    System::render(reg);
}

void Game::clean() {
    System::cleanRender(reg);
}
