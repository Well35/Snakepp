#include "Game.h"
#include <SDL.h>
#include <iostream>
#include <cmath>

Game::Game() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " <<  SDL_GetError() << std::endl;
    }
    m_gameRunning = true;
    m_currentTime = 0;
    dir = Direction::RIGHT;
    move_fruit();
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
            snakePos.x -= snake.get_segmentSize();
            break;
        case Direction::RIGHT:
            snakePos.x += snake.get_segmentSize();
            break;
        case Direction::UP:
            snakePos.y -= snake.get_segmentSize();
            break;
        case Direction::DOWN:
            snakePos.y += snake.get_segmentSize();
            break;
    }
    snake.set_headPos(snakePos.x, snakePos.y);
    snake.move();

    // Handles fruit collision and grows snake on collision
    //
    if (snake.get_headPos().x == m_fruit.x and snake.get_headPos().y == m_fruit.y) {
        move_fruit();
        snake.grow(1);
    }

    // Handles collision between snake head and body
    //
    if (snake.check_collision()) {
        m_gameRunning = false;
    }

    SDL_Delay(60);
}

void Game::draw() {
    graphics.clear_screen();
    snake.draw(graphics);
    draw_fruit();
    graphics.show_screen();
}

void Game::move_fruit() {
    int rand_x = rand() % graphics.get_screen_width() / 16;
    int rand_y = rand() % graphics.get_screen_height() / 16;
    m_fruit = { rand_x * 16, rand_y * 16, 16, 16 };
}

void Game::draw_fruit() {
    graphics.render_rect(m_fruit, 255, 0, 0);
}
