#ifndef GAME_H
#define GAME_H

#include "gameboard.h"

	Player * playGame(Player * first, Player * second);
	Boolean makeMove(Player * player, Cell board[BOARD_HEIGHT][BOARD_WIDTH]);
	Boolean applyMove(Cell board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Cell token);
	unsigned gameScore(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token);
	void swapPlayers(Player ** first, Player ** second);
	void printPlayerDetail(Player * first, Player * second);

#endif
