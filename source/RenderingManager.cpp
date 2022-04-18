#include "RenderingManager.h"

#include <iostream>

#include "ServiceLocator.h"
#include "Settings.h"

RenderingManager::RenderingManager(bool& initResult) {
	initResult = initialize();
}

RenderingManager::~RenderingManager() {}

bool RenderingManager::initialize() {
	_window = WindowUniquePtr(SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN));

	
	if (_window == nullptr) {
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	_renderer = RendererUniquePtr(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED));
	if (_renderer == nullptr) {
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawBlendMode(_renderer.get(), SDL_BLENDMODE_MOD);
	SDL_SetWindowIcon(_window.get(), ServiceLocator::getResourceManager()->loadSurface(WINDOW_ICON).get());

	return true;
}

SDL_Renderer* RenderingManager::getRenderer() const {
	return _renderer.get();
}
