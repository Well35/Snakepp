#include "Game.h"
#include <SDL.h>
#include <iostream>

Game::Game() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " <<  SDL_GetError() << std::endl;
    }
    m_gameRunning = true;
    m_currentTime = 0;
    this->loop();
}

Game::~Game() {
    SDL_Quit();
}

void Game::loop() {
    while (m_gameRunning) {
        this->input();
        this->update();
        this->draw();
    }
}

void Game::input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_gameRunning = false;
            break;
        }
    }
}

void Game::update() {
    double lastTime = m_currentTime;
    double currentTime = SDL_GetTicks();
    double deltaTime = (currentTime - lastTime) / 1000.0f;

}

void Game::draw() {
    graphics.clear_screen();
    graphics.show_screen();
}
