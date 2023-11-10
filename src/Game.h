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
	Graphics graphics;
	Snake snake = {200,200};

	bool m_gameRunning;
	double m_currentTime;
	enum class Direction { LEFT, RIGHT, UP, DOWN };
	Direction dir;
};