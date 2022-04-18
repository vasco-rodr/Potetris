#include "MenuScreen.h"

#include "ApplicationState.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Settings.h"
#include "ServiceLocator.h"

static const uint8_t BUTTONS_X_POSITION = 20;
static const uint16_t BUTTONS_STARTING_Y_POSITION = 560;
static const uint8_t BUTTONS_VERTICAL_SPACING = 2;

static const float BUTTON_X_SCALE = BUTTONS_X_POSITION / (float) WINDOW_WIDTH;
static const float BUTTON_Y_SCALE = BUTTONS_STARTING_Y_POSITION / (float)WINDOW_HEIGHT;

MenuScreen::MenuScreen() : Screen(BACKGROUND_MENU_TEX, ApplicationState::Menu) {
	_playButton = std::make_unique<Button>(ServiceLocator::getResourceManager()->loadTexture(BUTTON_PLAY_TEX), nullptr);
	_playButton->setPosition((int) (WINDOW_WIDTH * BUTTON_X_SCALE), (int) (WINDOW_HEIGHT * BUTTON_Y_SCALE));
	_playButton->setAction([this]() { ServiceLocator::getStateManager()->changeState(ApplicationState::Play); });

	_howToButton = std::make_unique<Button>(ServiceLocator::getResourceManager()->loadTexture(BUTTON_HOW_TO_TEX), nullptr);
	_howToButton->setPosition(BUTTONS_X_POSITION, _playButton->getPosition().y + _playButton->getHeight() + BUTTONS_VERTICAL_SPACING);
	_howToButton->setAction([this]() { ServiceLocator::getStateManager()->changeState(ApplicationState::HelpMenu); });
	
	_highScoresButton = std::make_unique<Button>(ServiceLocator::getResourceManager()->loadTexture(BUTTON_HIGHSCORES_TEX), nullptr);
	_highScoresButton->setPosition(BUTTONS_X_POSITION, _howToButton->getPosition().y + _howToButton->getHeight() + BUTTONS_VERTICAL_SPACING);
	_highScoresButton->setAction([this]() { ServiceLocator::getStateManager()->changeState(ApplicationState::HighScores); });
}

MenuScreen::~MenuScreen() {}

void MenuScreen::renderScreenSpecificElements() {
	_howToButton->render();
	_highScoresButton->render();
	_playButton->render();
}

void MenuScreen::update() {
	_howToButton->update();
	_highScoresButton->update();
	_playButton->update();
}

void MenuScreen::handleKeyPress(const SDL_Keycode key) {}
