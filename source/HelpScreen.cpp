#include "HelpScreen.h"

#include "ApplicationState.h"
#include "Button.h"
#include "ServiceLocator.h"
#include "Settings.h"

HelpScreen::HelpScreen() : Screen(BACKGROUND_HOW_TO_TEX, ApplicationState::HelpMenu) {
	_backButton = std::make_unique<Button>(ServiceLocator::getResourceManager()->loadTexture(BUTTON_BACK_TEX), nullptr);
	_backButton->setPosition(TOP_BUTTONS_STARTING_X_LOCATION, TOP_BUTTONS_Y_LOCATION);
	_backButton->setAction([this]() { ServiceLocator::getStateManager()->changeState(ApplicationState::Menu); });
}

HelpScreen::~HelpScreen() {}

void HelpScreen::renderScreenSpecificElements() {
	_backButton->render();
}

void HelpScreen::update() {
	_backButton->update();
}

void HelpScreen::handleKeyPress(const SDL_Keycode key) {}