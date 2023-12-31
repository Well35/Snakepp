#include "Snake.h"

Snake::Snake(int initial_x, int initial_y) {
	m_headPos = { initial_x, initial_y };
	SDL_Rect r(initial_x, initial_y, m_segmentSize, m_segmentSize);
	m_body.push_back(r);
	m_growSize = 1;
}

void Snake::move() {
	SDL_Rect r(m_headPos.x, m_headPos.y, m_segmentSize, m_segmentSize);
	if (!(m_body.size() < m_growSize)) {
		m_body.pop_back();
	}
	m_body.push_front(r);
}

void Snake::draw(Graphics& graphics) {
	for (const auto& r : m_body) {
		graphics.render_rect(r, 0, 0, 255);
	}
}

void Snake::reset_snake() {
	m_body.clear();
	m_growSize = 1;
	m_headPos = { 320, 240 };
	SDL_Delay(100);
}

bool Snake::check_collision() {
	for (int i = 0; i < m_body.size(); i++) {
		SDL_Rect r = m_body[i];
		if (r.x == m_headPos.x and r.y == m_headPos.y and i > 0)
			return true;
	}
	return false;
}
