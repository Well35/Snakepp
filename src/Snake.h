#pragma once
#include "Vector2.h"
#include "Graphics.h"
#include <SDL.h>
#include <deque>

class Snake {
public:
	Snake(int initial_x, int initial_y);
	void move();
	void draw(Graphics& graphics);
	void grow(int x) { m_growSize += x; }
	bool check_collision();

	int get_segmentSize() { return m_segmentSize; }
	Vector2 get_headPos() { return m_headPos; }

	void set_headPos(int x, int y) { m_headPos = { x, y }; }
private:
	std::deque<SDL_Rect> m_body;
	int m_segmentSize;
	Vector2 m_headPos;
	int m_growSize;
};