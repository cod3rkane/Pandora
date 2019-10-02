//
// Created by Júlio César Lopes on 02/10/19.
//

#include "Game.h"
#include "../system/render.h"
#include "../components/Shader.h"
#include "../components/Render.h"

Game::Game() {

}

Game::~Game() {

}

void Game::init() {
    // init entities
    const Entity e = reg.create();

    reg.assign<Shader>(e);
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

    System::render(reg);
}

void Game::clean() {
    // add System to Clean things up
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
}