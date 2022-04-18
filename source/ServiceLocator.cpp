#include "ServiceLocator.h"

std::unique_ptr<AudioManager> ServiceLocator::_audioManagerService = nullptr;
std::unique_ptr<MouseManager> ServiceLocator::_mouseManagerService = nullptr;
std::unique_ptr<RenderingManager> ServiceLocator::_renderingManagerService = nullptr;
std::unique_ptr<ResourceManager> ServiceLocator::_resourceManagerService = nullptr;
std::unique_ptr<ScoreManager> ServiceLocator::_scoreManagerService = nullptr;
std::unique_ptr<StateManager> ServiceLocator::_stateManagerService = nullptr;


void ServiceLocator::registerServices() {
	_mouseManagerService = std::make_unique<MouseManager>();
	_scoreManagerService = std::make_unique<ScoreManager>();
	_stateManagerService = std::make_unique<StateManager>();
}

void ServiceLocator::registerAudioManager(bool& initResult) {
	_audioManagerService = std::make_unique<AudioManager>(initResult);
}

void ServiceLocator::registerRenderingManager(bool& initResult) {
	_renderingManagerService = std::make_unique<RenderingManager>(initResult);
}

void ServiceLocator::registerResourceManager(bool& initResult) {
	_resourceManagerService = std::make_unique<ResourceManager>(initResult);
}

AudioManager* ServiceLocator::getAudioManager() {
	return _audioManagerService.get();
}

MouseManager* ServiceLocator::getMouseManager() {
	return _mouseManagerService.get();
}

RenderingManager* ServiceLocator::getRenderingManager() {
	return _renderingManagerService.get();
}

ResourceManager* ServiceLocator::getResourceManager() {
	return _resourceManagerService.get();
}

ScoreManager* ServiceLocator::getScoreManager()
{
	return _scoreManagerService.get();
}

StateManager* ServiceLocator::getStateManager() {
	return _stateManagerService.get();
}