#ifndef CONFIG_H
#define CONFIG_H

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

const int SHOW_DURATION		= 1500;

#endif
