#include "GameObject.h"

#include "ServiceLocator.h"

GameObject::GameObject() {
	_texture = nullptr;
	_sourceRect = SDL_Rect();
	_destinationRect = SDL_Rect();
	_position = SDL_Point();
	_isVisible = false;
}

GameObject::~GameObject() {
	_texture = nullptr;
}

void GameObject::initialize() {}

void GameObject::update() {}

void GameObject::render() const {
	if (!_isVisible) {
		return;
	}

	SDL_RenderCopy(ServiceLocator::getRenderingManager()->getRenderer(), _texture.get(), nullptr, &_destinationRect);
}

void GameObject::setTexture(std::shared_ptr<SDL_Texture> texture) {
	_texture = texture;
	SDL_QueryTexture(_texture.get(), nullptr, nullptr, &_sourceRect.w, &_sourceRect.h);
	_destinationRect.w = static_cast<int>(_sourceRect.w);
	_destinationRect.h = static_cast<int>(_sourceRect.h);
}

SDL_Point GameObject::getPosition() const {
	return _position;
}

void GameObject::setPosition(const SDL_Point position) {
	_position = position;
	_destinationRect.x = _position.x;
	_destinationRect.y = _position.y;
}

void GameObject::setPosition(const int x, const int y) {
	_position.x = x;
	_position.y = y;
	_destinationRect.x = _position.x;
	_destinationRect.y = _position.y;
}

void GameObject::setVisibility(const bool isVisible) {
	_isVisible = isVisible;
}

bool GameObject::isVisible() const {
	return _isVisible;
}

int GameObject::getWidth() const {
	return _destinationRect.w;
}

int GameObject::getHeight() const {
	return _destinationRect.h;
}
