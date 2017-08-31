#ifndef PLAYER_H
#define PLAYER_H

#include "utility.h"

typedef enum cell
{
    BLANK, RED, CYAN
} Cell;

/* Color codes required to display the tokens on the board. */
#define COLOR_RED   "\33[31m"
#define COLOR_CYAN  "\33[36m"
#define COLOR_RESET "\33[0m"

/* The maximum length of a player name. */
#define NAMELEN 20

typedef struct player
{
    char name[NAMELEN + NULL_SPACE];
    Cell token;
    unsigned score;
} Player;

	void initFirstPlayer(Player * player);
	void initSecondPlayer(Player * player, Cell token);
	Boolean validateName(Player * player);

#endif
