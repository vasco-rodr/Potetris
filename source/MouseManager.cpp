#include "MouseManager.h"

MouseManager::MouseManager() {
	_position = SDL_Point();
	_currentFrameState = MouseState::ButtonUp;
	_pastFrameState = MouseState::ButtonUp;
}

MouseManager::~MouseManager() {}

SDL_Point MouseManager::getPosition() const {
	return _position;
}

bool MouseManager::isLeftButtonPressed() const {
	if (_currentFrameState == MouseState::ButtonDown) {
		return (_pastFrameState == MouseState::ButtonUp);
	}

	return false;
}

void MouseManager::onMouseMove(SDL_Event& event) {
	_position.x = event.motion.x;
	_position.y = event.motion.y;
}

void MouseManager::onMouseButtonDown(SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT) {
		_currentFrameState = MouseState::ButtonDown;
	}
}

void MouseManager::onMouseButtonUp(SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT) {
		_currentFrameState = MouseState::ButtonUp;
	}
}

void MouseManager::updateState() {
	_pastFrameState = _currentFrameState;
}

void MouseManager::handleEvent(SDL_Event& event) {
	switch (event.type) {
		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;
		default:
			break;
	}
}