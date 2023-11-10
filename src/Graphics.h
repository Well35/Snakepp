#pragma once
#include <SDL.h>

class Graphics {
public:
	Graphics();
	~Graphics();
	void clear_screen();
	void show_screen();
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	SDL_Window* m_window = nullptr;
	SDL_Surface* m_screenSurface = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};