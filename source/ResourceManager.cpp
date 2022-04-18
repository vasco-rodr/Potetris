#include "ResourceManager.h"

#include <SDL_image.h>
#include <iostream>

#include "SdlSmartPointers.h"
#include "ServiceLocator.h"
#include "Settings.h"

ResourceManager::ResourceManager(bool& initResult) {
	initResult = initialize();
}

ResourceManager::~ResourceManager() {
	_textures.clear();
	_sounds.clear();
	_musics.clear();
	_fonts.clear();

	IMG_Quit();
	TTF_Quit();
}

bool ResourceManager::initialize() {
	if (!IMG_Init(IMG_INIT_PNG)) {
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() < 0) {
		std::cout << "SDL_TTF could not initialize! Error: " << TTF_GetError() << std::endl;
		return false;
	}

	return true;
}

std::shared_ptr<SDL_Texture> ResourceManager::loadTexture(const char* textureName) {
	const std::unordered_map<const char*, std::shared_ptr<SDL_Texture>>::const_iterator it = _textures.find(textureName);

	if (it != _textures.end()) {
		return it->second;
	}

	std::shared_ptr<SDL_Surface> surface = loadSurface(textureName);

	std::shared_ptr<SDL_Texture> texture (SDL_CreateTextureFromSurface(ServiceLocator::getRenderingManager()->getRenderer(), surface.get()), SDL_Deleter());
	
	if (texture == nullptr) {
		std::cout << "Unable to create texture from " << textureName << "! SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	_textures[textureName] = texture;

	return texture;
}

std::shared_ptr<SDL_Surface> ResourceManager::loadSurface(const char* fileName) {
	std::string path(ASSETS_FOLDER);
	
	std::shared_ptr<SDL_Surface> surface(IMG_Load(path.append(fileName).c_str()), SDL_Deleter());
	
	if (surface == nullptr) {
		std::cout << "Unable to load image " << fileName << "! SDL_image Error: " << IMG_GetError() << std::endl;
		return nullptr;
	}

	return surface;
}

std::shared_ptr<Mix_Chunk> ResourceManager::loadSound(const char* soundName) {
	const std::unordered_map<const char*, std::shared_ptr<Mix_Chunk>>::const_iterator it = _sounds.find(soundName);

	if (it != _sounds.end()) {
		return it->second;
	}

	std::string path(ASSETS_FOLDER);

	std::shared_ptr<Mix_Chunk> sound (Mix_LoadWAV(path.append(soundName).c_str()), SDL_Deleter());

	if (sound == nullptr) {
		std::cout << "Failed to load " << soundName << "sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return nullptr;
	}

	_sounds[soundName] = sound;

	return sound;
}

std::shared_ptr<Mix_Music> ResourceManager::loadMusic(const char* musicName) {
	const std::unordered_map<const char*, std::shared_ptr<Mix_Music>>::const_iterator it = _musics.find(musicName);

	if (it != _musics.end()) {
		return it->second;
	}

	std::string path(ASSETS_FOLDER);

	std::shared_ptr<Mix_Music> music (Mix_LoadMUS(path.append(musicName).c_str()),SDL_Deleter());

	if (music == nullptr) {
		std::cout << "Failed to load " << musicName << "music! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return nullptr;
	}

	_musics[musicName] = music;

	return music;
}

std::shared_ptr<TTF_Font> ResourceManager::loadFont(const char* fontName) {
	const std::unordered_map<const char*, std::shared_ptr<TTF_Font>>::const_iterator it = _fonts.find(fontName);

	if (it != _fonts.end()) {
		return it->second;
	}

	std::string path(ASSETS_FOLDER);

	std::shared_ptr<TTF_Font> font(TTF_OpenFont(path.append(fontName).c_str(), FONT_SIZE), SDL_Deleter());

	if (font == nullptr) {
		std::cout << "Failed to load " << fontName << "font! SDL_ttf Error: " << Mix_GetError() << std::endl;
		return nullptr;
	}

	_fonts[fontName] = font;

	return font;
}
