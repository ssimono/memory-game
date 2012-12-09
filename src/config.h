#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#ifdef RELEASE
static const char* SHARE_FOLDER = "/usr/share/memory-game/";
#else
static const char* SHARE_FOLDER = "share/";
#endif

const int NB_LINES		= 5;
const int NB_COLUMNS		= 4;

const int SQUARE_WIDTH		= 70;
const int SQUARE_HEIGHT		= 70;
const int SQUARE_MARGIN_RIGHT	= 5;
const int SQUARE_MARGIN_BOTTOM	= 5;

const int BOARD_ORIGIN_X	= SQUARE_MARGIN_RIGHT;
const int BOARD_ORIGIN_Y	= SQUARE_MARGIN_BOTTOM;

const int SCORE_PANEL_WIDTH     = 150;
const int SCORE_PANEL_HEIGHT    = 35;

const int HIDDEN_SQUARE_COLOR	= 0x27863f;
const int HOVER_SQUARE_COLOR	= 0x37964f;
const int FOUND_SQUARE_COLOR	= 0xff0000;

const int BACKGROUND_COLOR	= 0xdfdfdf;

/*
 * Return screen height in pixels
 */
static int get_screen_height(int nb_players)
{
    return std::max(BOARD_ORIGIN_Y + NB_LINES * (SQUARE_HEIGHT + SQUARE_MARGIN_BOTTOM),
	       nb_players * SCORE_PANEL_HEIGHT);
}

/*
 * Return screen width in pixels
 */
static int get_screen_width()
{
    return	BOARD_ORIGIN_X +
		NB_COLUMNS * (SQUARE_WIDTH + SQUARE_MARGIN_RIGHT) +
		SCORE_PANEL_WIDTH;
}

/*
 * Struct used to store settings set at runtime
 */
struct Settings
{
    // string defining type and numers of players:
    std::string players_list;

    // Milliseconds during which cards are shown:
    int show_duration;
};

#endif
