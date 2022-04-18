/**
 * @file	ResourceManager.h.
 *
 * Declares the Resource Manager class.
 */

#pragma once

#include <memory>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <unordered_map>

struct SDLTextureDeleter {
	void operator()(SDL_Texture* texture) const {
		SDL_DestroyTexture(texture);
	}
};

class ResourceManager {

public:
	/**
	 * RenderingManager constructor.
	 *
	 * @param initResult Out parameter with the result of SDL_image and SDL_TTF initialization.
	 */
	ResourceManager(bool& initResult);
	~ResourceManager();

	/**
	 * Loads a texture into the manager.
	 *
	 * @param	textureName The name of the texture.
	 *
	 * @return	Null if it fails, else the texture.
	 */
	std::shared_ptr<SDL_Texture> loadTexture(const char* textureName);

	/**
	 * Loads a surface.
	 *
	 * @param	fileName The name of the file that feeds the surface.
	 *
	 * @return	Null if it fails, else the surface.
	 */
	std::shared_ptr<SDL_Surface> loadSurface(const char* fileName);
	
	/**
	 * Loads a sound into the manager.
	 *
	 * @param	name The name of the sound.
	 *
	 * @return	Null if it fails, else the sound.
	 */
	std::shared_ptr<Mix_Chunk> loadSound(const char* name);

	/**
	 * Loads a music into the manager.
	 *
	 * @param	name The name of the music.
	 *
	 * @return	Null if it fails, else the music.
	 */
	std::shared_ptr<Mix_Music> loadMusic(const char* name);

	/**
	 * Loads a font into the manager.
	 *
	 * @param	name The name of the font.
	 *
	 * @return	Null if it fails, else the font.
	 */
	std::shared_ptr<TTF_Font> loadFont(const char* name);

private:
	/**
	 * Initializes SDL_image and SDL_TTF.
	 *
	 * @return	true if both SDL_image and SDL_TTF were initialized correctly, false otherwise.
	 */
	bool initialize();
	
	std::unordered_map<const char*, std::shared_ptr<SDL_Texture>> _textures;
	std::unordered_map<const char*, std::shared_ptr<Mix_Chunk>> _sounds;
	std::unordered_map<const char*, std::shared_ptr<Mix_Music>> _musics;
	std::unordered_map<const char*, std::shared_ptr<TTF_Font>> _fonts;
};