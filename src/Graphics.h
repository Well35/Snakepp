#pragma once
#include <SDL.h>

class Graphics {
public:
	Graphics();
	~Graphics();
	void clear_screen();
	void show_screen();
	void render_rect(const SDL_Rect& box, int r, int g, int b);

	int get_screen_width() { return SCREEN_WIDTH; }
	int get_screen_height() { return SCREEN_HEIGHT; }
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	SDL_Window* m_window = nullptr;
	SDL_Surface* m_screenSurface = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};