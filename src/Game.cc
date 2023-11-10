#include "Game.h"
#include <SDL.h>
#include <iostream>

Game::Game() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " <<  SDL_GetError() << std::endl;
    }
    m_gameRunning = true;
    m_currentTime = 0;
    dir = Direction::RIGHT;
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
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    dir = Direction::UP;
                    break;
                case SDL_SCANCODE_A:
                    dir = Direction::LEFT;
                    break;
                case SDL_SCANCODE_S:
                    dir = Direction::DOWN;
                    break;
                case SDL_SCANCODE_D:
                    dir = Direction::RIGHT;
                    break;
            }
        }
    }
}

void Game::update() {
    double lastTime = m_currentTime;
    double currentTime = SDL_GetTicks();
    double deltaTime = (currentTime - lastTime) / 1000.0f;

    Vector2 snakePos = snake.get_headPos();
    switch (dir) {
        case Direction::LEFT:
            snakePos.x -= 16;
            break;
        case Direction::RIGHT:
            snakePos.x += 16;
            break;
        case Direction::UP:
            snakePos.y -= 16;
            break;
        case Direction::DOWN:
            snakePos.y += 16;
            break;
    }
    std::cout << snakePos.x << " " << snakePos.y << " " << std::endl;
    snake.set_headPos(snakePos.x, snakePos.y);
    snake.move();
    SDL_Delay(40);
}

void Game::draw() {
    graphics.clear_screen();
    snake.draw(graphics);
    graphics.show_screen();
}
