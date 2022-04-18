/**
 * @file	Application.h.
 *
 * Declares the Application class.
 *
 * The application object. It controls the application main loop,
 * updating and rendering the objects according to the application state.
 */

#pragma once

class Application {

public:
	Application();
	~Application();

	/**
	 * Initializes the state of the application.
	 *
	 * @return	True if it succeeds, false if it fails.
	 */
	bool initialize();

	/**
	 * Runs the application.
	 */
	void run();

private:
	/**
	 * Initializes the SDL libraries, rendering and window.
	 *
	 * @return	True if it succeeds, false if it fails.
	 */
	bool initializeSdl();

	/**
	 * Handles SDL events.
	 */
	void handleEvents();

	bool _quit;
};
