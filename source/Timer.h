/**
 * @file	Timer.h.
 *
 * Declares the Timer class.
 *
 * Object that handles time.
 * It has all the basic functions to start/stop/pause/unpause
 * a timer and check its status.
 */

#pragma once

#include <stdint.h>

class Timer {

public:
	Timer();
	~Timer();

	/**
	 * Starts the timer.
	 */
	void start();

	/**
	 * Stops the timer.
	 */
	void stop();

	/**
	 * Pauses the timer.
	 */
	void pause();

	/**
	 * Unpauses the timer, setting the new startTicks value.
	 */
	void unpause();

	/**
	 * Gets the game time since the game has started.
	 *
	 * @return	The time.
	 */
	uint32_t getTime() const;

	/**
	 * Checks if the timer is in a started state.
	 *
	 * @return	True if started, false if not.
	 */
	bool isStarted() const;

	/**
	 * Checks if the timer is in a paused state.
	 *
	 * @return	True if paused, false if not.
	 */
	bool isPaused() const;

private:
	uint32_t _startTicks;
	uint32_t _pausedTicks;

	bool _paused;
	bool _started;
};