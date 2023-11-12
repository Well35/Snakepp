#include "Game.h"
#include <SDL.h>
#include <iostream>
#include <cmath>

Game::Game() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }
    m_gameRunning = true;
    m_currentTime = 0;
    m_rectSizes = 16;
    m_playArea = {graphics.get_border_size(), 
                  graphics.get_border_size(), 
                  graphics.get_screen_width() - graphics.get_border_size(),
                  graphics.get_screen_height() - graphics.get_border_size()
                 };
    snake.set_segmentSize(m_rectSizes);
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
                    if (dir == Direction::DOWN) break;
                    dir = Direction::UP;
                    break;
                case SDL_SCANCODE_A:
                    if (dir == Direction::RIGHT) break;
                    dir = Direction::LEFT;
                    break;
                case SDL_SCANCODE_S:
                    if (dir == Direction::UP) break;
                    dir = Direction::DOWN;
                    break;
                case SDL_SCANCODE_D:
                    if (dir == Direction::LEFT) break;
                    dir = Direction::RIGHT;
                    break;
            }
        }
    }
}

void Game::update() {
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
        snake.reset_snake();
    }
    // Handles collision with snake going outside border
    //
    if (snake.get_headPos().x < m_playArea.x or snake.get_headPos().x >= m_playArea.x + m_playArea.w) {
        snake.reset_snake();
    }
    else if (snake.get_headPos().y < m_playArea.y or snake.get_headPos().y >= m_playArea.y + m_playArea.h) {
        snake.reset_snake();
    }

    SDL_Delay(60);
}

void Game::draw() {
    graphics.clear_screen();
    draw_play_area();
    snake.draw(graphics);
    draw_fruit();
    graphics.show_screen();
}

void Game::move_fruit() {
    int rand_x = rand() % m_playArea.w / m_rectSizes;
    int rand_y = rand() % m_playArea.h / m_rectSizes;
    m_fruit = { rand_x * m_rectSizes, rand_y * m_rectSizes, m_rectSizes, m_rectSizes };
}

void Game::draw_fruit() {
    graphics.render_rect(m_fruit, 255, 0, 0);
}

void Game::draw_play_area() {
    graphics.render_rect(m_playArea, 0, 0, 0);
}
