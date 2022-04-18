#include "HighScoresScreen.h"

#include "ApplicationState.h"
#include "Button.h"
#include "ServiceLocator.h"
#include "Settings.h"

static const uint8_t LINE_VERTICAL_SPACING = 40;
static const char* DATE_LABEL = "DATE: ";
static const char* SCORE_DATE_SPACING = "   ";

HighScoresScreen::HighScoresScreen() : Screen(BACKGROUND_HIGHSCORES_TEX, ApplicationState::HighScores) {
	_backButton = std::make_unique<Button>(ServiceLocator::getResourceManager()->loadTexture(BUTTON_BACK_TEX), nullptr);
	_backButton->setPosition(TOP_BUTTONS_STARTING_X_LOCATION, TOP_BUTTONS_Y_LOCATION);
	_backButton->setAction([this]() { ServiceLocator::getStateManager()->changeState(ApplicationState::Menu); });
}

HighScoresScreen::~HighScoresScreen() {}

void HighScoresScreen::renderScreenSpecificElements() {
	_backButton->render();
	renderHighScores();
}

void HighScoresScreen::update() {
	_backButton->update();
}

void HighScoresScreen::handleKeyPress(const SDL_Keycode key) {}

void HighScoresScreen::renderHighScores() const {
	SDL_Rect rect;
	SDL_Surface* surface;
	SDL_Texture* texture;
	uint8_t lineYLocation = 0;
	
	for(const auto highScore : ServiceLocator::getScoreManager()->getHighScores()) {
		surface = TTF_RenderText_Blended(ServiceLocator::getResourceManager()->loadFont(FONT_NAME).get(),
			(SCORE_LABEL + std::to_string(highScore._score) + SCORE_DATE_SPACING + DATE_LABEL + highScore._date).c_str(),
			FONT_COLOR);

		texture = SDL_CreateTextureFromSurface(ServiceLocator::getRenderingManager()->getRenderer(), surface);
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);

		rect.x = (WINDOW_WIDTH / 2) - (rect.w / 2);
		rect.y = WINDOW_HEIGHT/2 + lineYLocation;

		SDL_RenderCopy(ServiceLocator::getRenderingManager()->getRenderer(), texture, nullptr, &rect);

		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		surface = nullptr;
		texture = nullptr;

		lineYLocation += LINE_VERTICAL_SPACING;
	}
}
