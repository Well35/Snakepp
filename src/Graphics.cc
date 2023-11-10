#include "Graphics.h"
#include <iostream>

Graphics::Graphics() {
	m_window = SDL_CreateWindow("Snake++", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (!m_window) {
		std::cout << "Could not create window. Error: " << SDL_GetError() << std::endl;
	}
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_renderer) {
		std::cout << "Could not create renderer. Error: " << SDL_GetError() << std::endl;
	}
}

Graphics::~Graphics() {
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
}

void Graphics::clear_screen() {
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
}

void Graphics::show_screen() {
	SDL_RenderPresent(m_renderer);
}
