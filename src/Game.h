#pragma once
#include "Graphics.h"
#include "Snake.h"

class Game {
public:
	Game();
	~Game();
private:
	void loop();
	void input();
	void update();
	void draw();
	void move_fruit();
	void draw_fruit();
	Graphics graphics;
	Snake snake{320,240};

	int m_rectSizes;
	bool m_gameRunning;
	double m_currentTime;
	enum class Direction { LEFT, RIGHT, UP, DOWN };
	Direction dir;

	SDL_Rect m_fruit;
};