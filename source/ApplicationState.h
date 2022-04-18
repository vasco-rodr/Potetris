#pragma once

/**
 * Values that represent the possible states of the application.
 */
enum class ApplicationState : uint8_t {
	GameOver,
	HelpPause,
	HelpMenu,
	HighScores,
	Menu,
	Pause,
	Play
};