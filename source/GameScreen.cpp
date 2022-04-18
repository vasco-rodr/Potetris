#include "GameScreen.h"

#include <string>

#include "ApplicationState.h"
#include "Board.h"
#include "Button.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "Settings.h"
#include "Timer.h"

static const uint16_t GAME_OVER_DELAY = 2000;
static const uint8_t SCORE_Y_LOCATION = 10;
static const uint8_t SCORE_TEXT_WRAP_LENGTH = 200;

GameScreen::GameScreen() : Screen(BACKGROUND_GAME_TEX, ApplicationState::Play) {
	initializePauseButton();
	initializeSoundButton();

	_pauseTexture = ServiceLocator::getResourceManager()->loadTexture(PAUSE_TEX);
	_isPaused = false;
	_timer = std::make_unique<Timer>();
	_board = std::make_unique<Board>();

	_timer->start();
	ServiceLocator::getScoreManager()->resetScore();
}

void GameScreen::initializePauseButton() {
	_pauseButton = std::make_unique<Button>(ServiceLocator::getResourceManager()->loadTexture(BUTTON_PAUSE_TEX), nullptr);
	_pauseButton->setPosition(TOP_BUTTONS_STARTING_X_LOCATION, TOP_BUTTONS_Y_LOCATION);
	_pauseButton->setAction([this]() { togglePause(); });
}

void GameScreen::initializeSoundButton() {
	_soundButton = std::make_unique<Button>(ServiceLocator::getResourceManager()->loadTexture(BUTTON_SOUNDON_TEX),
											ServiceLocator::getResourceManager()->loadTexture(BUTTON_SOUNDOFF_TEX));
	_soundButton->setPosition(_pauseButton->getWidth() * 1.5, TOP_BUTTONS_Y_LOCATION);

	_soundButton->setAction([this]() { ServiceLocator::getAudioManager()->toggleMusic(); });
}

GameScreen::~GameScreen() {
	_timer.reset(nullptr);
}

void GameScreen::renderScreenSpecificElements() {
	_board->render();

	if (_isPaused) {
		SDL_RenderCopy(ServiceLocator::getRenderingManager()->getRenderer(), _pauseTexture.get(), nullptr, nullptr);
	}
	else {
		renderScore();
	}
	
	_pauseButton->render();
	_soundButton->render();
	
}

void GameScreen::update() {
	_pauseButton->update();
	_soundButton->update();
	_board->update(_timer->getTime() - _updateTime);
	
	if (_board->isGameOver()) {
		SDL_Delay(GAME_OVER_DELAY);
		ServiceLocator::getScoreManager()->saveScore();
		ServiceLocator::getStateManager()->changeState(ApplicationState::GameOver);
	}

	_updateTime = _timer->getTime();
}

void GameScreen::handleKeyPress(SDL_Keycode key) {
	if (!_isPaused) {
		_board->handleKeyPress(key);
	}
}

void GameScreen::togglePause() {
	if (_isPaused) {
		_timer->unpause();
	} else {
		_timer->pause();
	}

	_isPaused = !_isPaused;
}

void GameScreen::renderScore() const {	
	SDL_Rect rect;
	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(ServiceLocator::getResourceManager()->loadFont(FONT_NAME).get(),
														(SCORE_LABEL + std::to_string(ServiceLocator::getScoreManager()->getScore())).c_str(),
														FONT_COLOR,
														SCORE_TEXT_WRAP_LENGTH);
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ServiceLocator::getRenderingManager()->getRenderer(), surface);
	SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);

	rect.x = (WINDOW_WIDTH / 2) - (rect.w / 2);
	rect.y = SCORE_Y_LOCATION;

	SDL_RenderCopy(ServiceLocator::getRenderingManager()->getRenderer(), texture, nullptr, &rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	surface = nullptr;
	texture = nullptr;
}
