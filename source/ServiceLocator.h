/**
 * @file	ServiceLocator.h.
 *
 * Declares the ServiceLocator class.
 *
 * Provides an access point to multiple services
 * of the game without coupling user classes to
 * the implementation classes.
 */

#pragma once

#include <memory>

#include "AudioManager.h"
#include "MouseManager.h"
#include "RenderingManager.h"
#include "ResourceManager.h"
#include "ScoreManager.h"
#include "StateManager.h"

class ServiceLocator {
public:
    /**
     * Gets the audio manager instance.
     *
     * @return The audio manager instance.
     */
    static AudioManager* getAudioManager();

    /**
     * Gets the mouse manager instance.
     *
     * @return The mouse manager instance.
     */
    static MouseManager* getMouseManager();

    /**
     * Gets the resource manager instance.
     *
     * @return The resource manager instance.
     */
    static ResourceManager* getResourceManager();

    /**
     * Gets the rendering manager instance.
     *
     * @return The rendering manager instance.
     */
    static RenderingManager* getRenderingManager();

    /**
	 * Gets the score manager instance.
	 *
	 * @return The score manager instance.
	 */
    static ScoreManager* getScoreManager();
	
    /**
     * Gets the state manager instance.
     *
     * @return The state manager instance.
     */
    static StateManager* getStateManager();

    /**
     * Registers non-SDL services.
     */
    static void registerServices();

    /**
     * Registers the Audio Manager.
     *
     * @param initResult Out parameter with the result of SDL_mixer's initialization.
     */
    static void registerAudioManager(bool& initResult);

    /**
     * Registers the Rendering Manager.
     *
     * @param initResult Out parameter with the result of SDL's window and rendering initialization.
     */
    static void registerRenderingManager(bool& initResult);

    /**
     * Registers the Resource Manager.
     *
     * @param initResult Out parameter with the result of SDL_image and SDL_TTF initialization.
     */
    static void registerResourceManager(bool& initResult);

private:
    static std::unique_ptr<AudioManager> _audioManagerService;
    static std::unique_ptr<MouseManager> _mouseManagerService;
    static std::unique_ptr<RenderingManager> _renderingManagerService;
    static std::unique_ptr<ResourceManager> _resourceManagerService;
    static std::unique_ptr<ScoreManager> _scoreManagerService;
    static std::unique_ptr<StateManager> _stateManagerService;
};
