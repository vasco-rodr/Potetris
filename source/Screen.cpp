#include "Screen.h"

#include "Application.h"
#include "ApplicationState.h"
#include "ServiceLocator.h"

Screen::Screen(const char* backgroundTexture, const ApplicationState applicationState) : _state(applicationState) {
	_backgroundTexture = ServiceLocator::getResourceManager()->loadTexture(backgroundTexture);
}

Screen::~Screen() {
	_backgroundTexture = nullptr;
}

ApplicationState Screen::getState() const {
	return _state;
}

void Screen::render() {
	SDL_Renderer* renderer = ServiceLocator::getRenderingManager()->getRenderer();
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, _backgroundTexture.get(), nullptr, nullptr);
	
	renderScreenSpecificElements();
	SDL_RenderPresent(renderer);
}

void Screen::run()
{
	update();
	render();
}