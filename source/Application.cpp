#include "Application.h"

#include <ctime>
#include <iostream>

#include "ServiceLocator.h"
#include "Settings.h"
#include "Timer.h"

Application::Application() {
	_quit = false;
}

Application::~Application() {
	SDL_Quit();
}

bool Application::initialize() {
	if (!initializeSdl()) {
		return false;
	}

	ServiceLocator::registerServices();

	srand(static_cast<uint32_t>(time(0)));

	return true;
}

bool Application::initializeSdl() {
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	bool wasImageFontInitialized;
	ServiceLocator::registerResourceManager(wasImageFontInitialized);
	if (!wasImageFontInitialized) {
		return false;
	}

	bool wasAudioInitialized;
	ServiceLocator::registerAudioManager(wasAudioInitialized);
	if (!wasAudioInitialized) {
		return false;
	}

	bool wasRenderInitialized;
	ServiceLocator::registerRenderingManager(wasRenderInitialized);
	return wasRenderInitialized;
}

void Application::run() {
	ServiceLocator::getAudioManager()->playMusic();

	Timer capTimer;

	while (!_quit) {
		capTimer.start();

		handleEvents();
		
		ServiceLocator::getStateManager()->run();

		const uint32_t frameTicks = capTimer.getTime();
		if (frameTicks < SCREEN_TICKS_PER_FRAME) {
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}

		ServiceLocator::getMouseManager()->updateState();
	}
}

void Application::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			_quit = true;
			break;

		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			ServiceLocator::getMouseManager()->handleEvent(event);
			break;

		case SDL_KEYUP:
		case SDL_KEYDOWN:
			ServiceLocator::getStateManager()->handleKeyboardInput(event);
			break;

		default:
			break;
		}
	}
}
