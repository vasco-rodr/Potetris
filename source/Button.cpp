#include "Button.h"

#include "ServiceLocator.h"
#include "Settings.h"

Button::Button(std::shared_ptr<SDL_Texture> mainTexture, std::shared_ptr<SDL_Texture> secondaryTexture) {
	_isVisible = true;
	_wasPressed = false;
	_mainTexture = mainTexture;
	_secondaryTexture = secondaryTexture;
	
	setTexture(_mainTexture);
}

Button::~Button() {
	_mainTexture = nullptr;
	_secondaryTexture = nullptr;
	_action = nullptr;
}

void Button::onClick() {
	_action();
	swapTexture();
	ServiceLocator::getAudioManager()->playSound(BUTTON_CLICK_SOUND);
}

void Button::swapTexture() {
	if (_secondaryTexture != nullptr) {
		if (_texture == _mainTexture) {
			setTexture(_secondaryTexture);
		}
		else {
			setTexture(_mainTexture);
		}
	}
}

void Button::setAction(const std::function<void()>& action) {
	_action = action;
}

void Button::setIsHovered(const bool isHovered) {
	_isHovered = isHovered;

	if (_isHovered) {
		SDL_SetTextureColorMod(_texture.get(), 255, 200, 62);
	} else {
		SDL_SetTextureColorMod(_texture.get(), 255, 255, 255);
	}
}

bool Button::isPositionInButton(const SDL_Point position) const {
	return (position.x > _position.x)
		&& (position.x < _position.x + getWidth())
		&& (position.y > _position.y)
		&& (position.y < _position.y + getHeight());
}

void Button::update() {
	if (isPositionInButton(ServiceLocator::getMouseManager()->getPosition())) {
		setIsHovered(true);

		if (ServiceLocator::getMouseManager()->isLeftButtonPressed()) {
			onClick();
		}

	} else if (_isHovered) {
		setIsHovered(false);
	}
}
