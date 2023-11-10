#include "Snake.h"

Snake::Snake(int initial_x, int initial_y) {
	m_segmentSize = 16;
	m_headPos = { initial_x, initial_y };
	SDL_Rect r(initial_x, initial_y, m_segmentSize, m_segmentSize);
	m_body.push_back(r);
	m_growSize = 1;
}

void Snake::move() {
	SDL_Rect r(m_headPos.x, m_headPos.y, m_segmentSize, m_segmentSize);
	if (!(m_body.size() < m_growSize)) {
		m_body.pop_front();
	}
	m_body.push_back(r);
}

void Snake::draw(Graphics& graphics) {
	for (const auto& r : m_body) {
		graphics.render_rect(r, 0, 0, 255);
	}
}
