#include "gameboard.h"

/* INITIALIZE GAMEBOARD */
/* Everything becomes set to a blank eNum, a few pieces are set */
void initBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int x, y; /* Index for board array */
	
	/* Loop through the whole 2 dimensional array and
	Initialize all tokens to BLANK */
	for (y=0; y < BOARD_HEIGHT; y++)
		for (x=0; x < BOARD_WIDTH; x++)
			board[x][y] = BLANK;
	
	/* Manually initialize starting tokens */
	board[3][3] = RED;
	board[3][4] = CYAN;
	board[4][3] = CYAN;
	board[4][4] = RED;
}

/* PRINT GAMEBOARD */
/* Will reprint each turn, checks what value the array holds and prints
 a colour accordingly */
void displayBoard(
    Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * first, Player * second)
{
	int x,y; /* Index for gameboard 2D array */

	/* Print initial columns */
	printf("\n     1   2   3   4   5   6   7   8\n"
		"====================================\n");
	
	/* Begin looping through 'y' rows to print gameboard */
	for (y = 0; y < BOARD_HEIGHT; y++)
	{	
		/* Print row number */
		printf(" %d | ", y+1);

		/* Loop through 'x' columns to print tokens */
		for (x = 0; x < BOARD_WIDTH; x++)
		{
			/* Check array to print correct colour */
			if (board[x][y] == BLANK)
				printf("%s ", COLOR_RESET);

			else if (board[x][y] == RED)
				printf("%s%s", COLOR_RED, "O"); 

			else if (board[x][y] == CYAN)
				printf("%s%s", COLOR_CYAN, "O");
			
			/* Automatically reset colour */
			printf("%s | ", COLOR_RESET);
		}
	
		/* Print row lines */
		if (y < 7)
			printf("\n------------------------------------\n");
	} 
	
	/* Print final row */
	printf("\n====================================\n");
}
