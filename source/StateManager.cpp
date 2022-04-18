#include "StateManager.h"

#include "ApplicationState.h"
#include "MenuScreen.h"
#include "GameOverScreen.h"
#include "GameScreen.h"
#include "HelpScreen.h"
#include "HighScoresScreen.h"

StateManager::StateManager() : _applicationState(ApplicationState::Menu) {}

StateManager::~StateManager() {}

void StateManager::pushState() {
	if ((_activeScreen != nullptr)
		&& (_applicationState == _activeScreen->getState())) {
		return;
	}

	_activeScreen = nullptr;
	switch (_applicationState) {
		case ApplicationState::Menu:
			_activeScreen = std::make_unique<MenuScreen>();
			break;
		case ApplicationState::HelpMenu:
			_activeScreen = std::make_unique<HelpScreen>();
			break;
		case ApplicationState::HighScores:
			_activeScreen = std::make_unique<HighScoresScreen>();
			break;
		case ApplicationState::Play:
			_activeScreen = std::make_unique<GameScreen>();
			break;
		case ApplicationState::GameOver:
			_activeScreen = std::make_unique<GameOverScreen>();
			break;
		default:
			break;
	}
}

void StateManager::changeState(ApplicationState applicationState) {
	_applicationState = applicationState;
}

void StateManager::run() {
	pushState();
	_activeScreen->run();
}

void StateManager::handleKeyboardInput(SDL_Event &event) const {
	if (event.type == SDL_KEYDOWN) {
		_activeScreen->handleKeyPress(event.key.keysym.sym);
	}
}
