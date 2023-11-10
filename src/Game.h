#pragma once
#include "Graphics.h"

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

	bool m_gameRunning;
	double m_currentTime;
};