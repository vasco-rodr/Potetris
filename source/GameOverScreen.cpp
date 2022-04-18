#include "GameOverScreen.h"

#include "ApplicationState.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Settings.h"
#include "ServiceLocator.h"

GameOverScreen::GameOverScreen() : Screen(BACKGROUND_GAMEOVER_TEX, ApplicationState::GameOver) {
	_quitButton = std::make_unique<Button>(ServiceLocator::getResourceManager()->loadTexture(BUTTON_BACK_TEX), nullptr);
	_quitButton->setPosition(TOP_BUTTONS_STARTING_X_LOCATION, TOP_BUTTONS_Y_LOCATION);
	_quitButton->setAction([this]() { ServiceLocator::getStateManager()->changeState(ApplicationState::Menu); });
}

GameOverScreen::~GameOverScreen() {}

void GameOverScreen::renderScreenSpecificElements() {
	_quitButton->render();
}

void GameOverScreen::update() {
	_quitButton->update();
}

void GameOverScreen::handleKeyPress(const SDL_Keycode key) {}
