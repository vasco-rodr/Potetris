#pragma once

#include <memory>
#include <SDL_mixer.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL_video.h>

struct SDL_Deleter {
	void operator()(SDL_Surface* ptr) { if (ptr) SDL_FreeSurface(ptr); }
	void operator()(SDL_Texture* ptr) { if (ptr) SDL_DestroyTexture(ptr); }
	void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
	void operator()(SDL_Window* ptr) { if (ptr) SDL_DestroyWindow(ptr); }
	void operator()(Mix_Chunk* ptr) { if (ptr) Mix_FreeChunk(ptr); }
	void operator()(Mix_Music* ptr) { if (ptr) Mix_FreeMusic(ptr); }
	void operator()(TTF_Font* ptr) { if (ptr) TTF_CloseFont(ptr); }
};

// Unique Pointers
using SurfaceUniquePtr = std::unique_ptr<SDL_Surface, SDL_Deleter>;
using TextureUniquePtr = std::unique_ptr<SDL_Texture, SDL_Deleter>;
using RendererUniquePtr = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
using WindowUniquePtr = std::unique_ptr<SDL_Window, SDL_Deleter>;
using ChunkUniquePtr = std::unique_ptr<SDL_Window, SDL_Deleter>;
using MusicUniquePtr = std::unique_ptr<SDL_Window, SDL_Deleter>;
using FontUniquePtr = std::unique_ptr<SDL_Window, SDL_Deleter>;
