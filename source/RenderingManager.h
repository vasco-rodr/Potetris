/**
 * @file	RenderingManager.h.
 *
 * Declares the Rendering Manager class.
 */
#pragma once

#include <memory>
#include "SdlSmartPointers.h"

class RenderingManager {

public:
	/**
	 * RenderingManager constructor.
	 *
	 * @param initResult Out parameter with the result of SDL's window and rendering initialization.
	 */
	RenderingManager(bool& initResult);

	~RenderingManager();

	/**
	 * Gets the renderer.
	 *
	 * @return	SDL's renderer.
	 */
	SDL_Renderer* getRenderer() const;

private:
	/**
	 * Initializes  SDL's window and rendering.
	 *
	 * @return	True if it was initialized correctly, false otherwise.
	 */
	bool initialize();

	WindowUniquePtr _window;
	RendererUniquePtr _renderer;
};
