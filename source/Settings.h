#pragma once

#include <SDL.h>

//Window
static const uint16_t WINDOW_WIDTH = 500;
static const uint16_t WINDOW_HEIGHT = 750;
static const char* WINDOW_NAME = "POTETRIS";
static const char* WINDOW_ICON = "icon.png";

//Frame Rate
static const uint8_t SCREEN_FPS = 60;
static const uint64_t SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
static const uint32_t AVG_FPS_CAP = 2000000;

//Images
static const char* BACKGROUND_MENU_TEX = "menu.png";
static const char* BACKGROUND_GAME_TEX = "background.png";
static const char* BACKGROUND_GAMEOVER_TEX = "gameover.png";
static const char* BACKGROUND_HOW_TO_TEX = "howto.png";
static const char* BACKGROUND_HIGHSCORES_TEX = "highscores.png";
static const char* PAUSE_TEX = "pause.png";
static const char* BUTTON_PLAY_TEX = "play_button.png";
static const char* BUTTON_PAUSE_TEX = "pause_button.png";
static const char* BUTTON_HOW_TO_TEX = "howto_button.png";
static const char* BUTTON_HIGHSCORES_TEX = "highscores_button.png";
static const char* BUTTON_BACK_TEX = "back_button.png";
static const char* BUTTON_SOUNDON_TEX = "soundon_button.png";
static const char* BUTTON_SOUNDOFF_TEX = "soundoff_button.png";
static const char* COLOR_1_TEX = "1.png";
static const char* COLOR_2_TEX = "2.png";
static const char* COLOR_3_TEX = "3.png";
static const char* COLOR_4_TEX = "4.png";
static const char* COLOR_5_TEX = "5.png";

//Font
static const uint8_t FONT_SIZE = 24;
static const char* FONT_NAME = "font.ttf";
static const SDL_Color FONT_COLOR = { 56, 26, 6, 255 };

//Assets location
static const char* ASSETS_FOLDER = "assets/";
static const char* SCORES_FILE = "assets/scores.txt";

//Sounds
static const char* MUSIC = "music.mp3";
static const char* BUTTON_CLICK_SOUND = "button_click_sound.mp3";

//Piece
static const uint8_t PIECE_SIZE = 36;
static const uint8_t NUMBER_COLORS = 4;

//GameArea
static const uint8_t MAX_COLS = 8;
static const uint8_t MAX_ROWS = 16;
static const uint8_t BOTTOM_MARGIN = PIECE_SIZE * 2;
static const SDL_Point SPAWN_ZONE = { WINDOW_WIDTH/2 - PIECE_SIZE * 4, WINDOW_HEIGHT - BOTTOM_MARGIN };
static const uint8_t LEFT_STARTING_COL = 3;
static const uint8_t STARTING_ROW = 15;

//Time
static const uint16_t ACTIVE_MOVE_TIME = 600;
static const uint16_t IDLE_MOVE_TIME = 100;

//Scores
static const uint8_t TOTAL_SCORES = 5;
static const char* SCORE_LABEL = "SCORE: ";

//Button positioning
static const uint8_t TOP_BUTTONS_STARTING_X_LOCATION = 10;
static const uint8_t TOP_BUTTONS_Y_LOCATION = 5;