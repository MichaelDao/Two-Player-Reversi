#include "game.h"

/* THE GAME */
/* Where initialization is prepared to run the game loop */
Player * playGame(Player * first, Player * second)
{
	/* Declare pointers for swap method */
	Player *pointPlayer;
	Player *swapPlayer;

	/* Initialize the gameboard */
	Cell board[BOARD_WIDTH][BOARD_HEIGHT];
	initBoard(board);

	/* Initialize player 1 and 2 */
	initFirstPlayer(first);
	initSecondPlayer(second, first->token);

	/* Identify the player with the RED token, they will go first */
	if (first -> token == RED)
	{
		/* Player 1 is RED */
		pointPlayer = first;
		swapPlayer = second;
	}
	else
	{
		/* Player 2 is RED */
		pointPlayer = second;
		swapPlayer = first;
	}

	/* Begin game loop */
	for(;;)	
	{ 
		/* update player score */		
		first->score = gameScore(board, first->token);
		second->score = gameScore(board, second->token);			

		/* Print player details */
		printPlayerDetail(first, second);
	
		/* Print the gameboard */
		displayBoard(board, first, second);			

		/* If player enters nothing, stop game loop */
		if (!makeMove(pointPlayer, board))
			break;
		
		/* At the end of each turn, change turns */
		swapPlayers(&pointPlayer, &swapPlayer);
	}

	/* Identify the winner and return them to be printed */	
	if (first->score > second->score)
		/* Player one wins */
		return first;

	else if (first->score < second->score)
		/* Player two wins */
		return second;
	else 
		/* Both players are tied */
		return NULL;
}

/* MAKE A MOVE */
/* Checks and validates the input before passing it through to the apply 
move method */
Boolean makeMove(Player * player, Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{	
	/* Declare variables */
	char input[3 + EXTRA_SPACES]; /* Input variable */
	Boolean valid; /* Loop boolean for validation */
	const int BASE_10 = 10; /* Constant for base 10 conversion */
	char * endPtr; /* End pointer for string tokenizer */	
	int x, y; /* Index for the board position */	
	
	/* Enter validation, loop until valid move entered */
	do
	{
		/* Initialize boolean for validation */
		valid = TRUE;

		if (player->token == RED)
			/* Player RED */
			printf("%sIt is %s's turn.%s\n", 
				COLOR_RED, player->name, COLOR_RESET);	
		else
			/* Player CYAN */
			printf("%sIt is %s's turn.%s\n", 
				COLOR_CYAN, player->name, COLOR_RESET);	

		/* Prompt player for input */	
		printf( "Please enter x and y coordinates separated by a"
			" comma for the piece you wish to place: ");
	
		/* Capture user input */
		fgets(input, sizeof(input), stdin); 
	
		/* Return to the main menu when blank input entered */
		if (strlen(input) <= NULL_SPACE)
		{
			printf("\n%sReturning to main menu%s\n", 
				COLOR_RED, COLOR_RESET);
			return FALSE;	
		}
		
		/* Ensures that the input is within the length range */
		else if (input[strlen(input) - 1] != '\n') 
		{
			printf("\n%sYour input is way too long!%s\n", 
				COLOR_RED, COLOR_RESET);
			readRestOfLine();
			valid = FALSE;
		}
		
		/* If the input does not have a comma, it is not valid */
		else if (input[1] != ',') 
		{	
			printf("\n%sYour input reqires a comma!%s\n" 
				, COLOR_RED, COLOR_RESET);		
			valid = FALSE;	
		}

		/* Prevent commas from breaking validation */
		if (input[0] == ',' || input[2] == ',')
		{
			printf("\n%serror, please enter again!%s\n"
				, COLOR_RED, COLOR_RESET); 
			valid = FALSE;
		}

		/* If input is not ready for string tokenizer, loop again */
		if (!valid)
			continue;
		
		/* If input is valid for string tokenizer, extract x and y */
		else
		{	
			/* Use delimeter ',' to seperate values */	
			x = strtol(strtok(input, ","), &endPtr, BASE_10);
			y = strtol(strtok(NULL, ","), &endPtr, BASE_10);	
		
			/* If input is out of bounds, prompt again */
			if (x <= 0 || x > BOARD_WIDTH || y <= 0
				 || y > BOARD_HEIGHT)
			{
				printf("\n%sOut of bounds%s\n",	COLOR_RED, 
					COLOR_RESET);
				valid = FALSE;	
				continue;
			}

			/* If illegal character entered with then break! */
			else if (x == -1 || y == -1 || x == ',' || y == ',')
			{
				printf("\n%sYou entered an illegal input%s\n",
					COLOR_RED, COLOR_RESET);
				valid = FALSE;
				continue;	
			}
		}

		/* Validate legality of the move before capturing pieces */
		if (!applyMove(board, x-1, y-1, player->token))
			valid = FALSE;	

	} while (!valid); /* Loop again if valid boolean is false */

	/* When the piece has been captured, swap turns */
	return TRUE;
}

/* APPLY THE MOVE */
/* Determine wether the tokens are valid to be placed there. */ 
/* Will check to see if there is any possible moves in that coordinate. */
/* If the move is valid, start capturing the pieces */
Boolean applyMove
	(Cell board[BOARD_HEIGHT][BOARD_WIDTH], int x, int y, Cell token)
{
	/* row and col describe the direction to travel in for the algorithm */ 
	int row, col; /* -1 = Left, 0 = Straight, 1 = Right */		
	int lookRow, lookCol; /* Used for searching */	
	int valid = FALSE; /* Boolean to determine valid move */
	
	/* If there already exists a token, is not valid move! */	
	if (board[x][y] != BLANK)
	{
		printf("\nToken already exists here!\n");
		return FALSE;
	}
		
	/* Check all squares around the token (3x3) */
	for (row = -1; row <= 1; row++)	
		for (col = -1; col <=1; col++)
		{
			/* Check opponent token to see if move is valid */
			if (board[x + col][y + row] != token)	
			{
				/* Focus on new position */
				lookCol = x + col;
				lookRow = y + row;
			
				/* Continue loop if opponent token found */			
				while(board[lookCol][lookRow] != BLANK) 
				{	
					/* Step over one towards target */
					lookCol += col;
					lookRow += row;
		
					/* If we leave the board, stop */
					if (lookCol < 1 || lookCol > 8 
						|| lookRow < 1 || lookRow > 8)
						break;
					
					/* If own token found, valid move! */		
					if (board[lookCol][lookRow] == token)
					{
						/* Set original position to
 						 the players token */
						board[x][y] = token;				
						
						/* flag as valid move */
						valid = TRUE;

						/* Move backwards*/
						lookCol -= col;						
						lookRow -= row;
			
						/* Change opponent tokens */
						while (board[lookCol][lookRow]
							!= token)	
						{
							/* Capture opponent */
							board[lookCol][lookRow]
								= token;
							
							/* Move backwards */
							lookCol -= col;
							lookRow -= row;
						}
						/* Check the next position */
						break;		
					}		
				}
			}
		}

	/* After checking all squares, determine if anything has changed */
	if (valid)
		/* Pieces have been captured, ready to swap players */ 
		return TRUE;
	else
	{
		/* If all surrounding squares do not show a possible move,
		return false to identify that this move is not valid. */
		printf("\n%sThis move doesn't work!%s\n",
			COLOR_RED, COLOR_RESET);
		return FALSE;
	}	
}

/* GAME SCORE */
/* Simply counts how many locations contain the token specified on board. */
unsigned gameScore(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token)
{
	unsigned int tokenCount = 0; /* Value to be returned to caller */ 
	int x,y; /* Index for the board coordinates */

	/* Loop through gameboard and count player tokens */
	for (y = 0; y < BOARD_HEIGHT; y++)
		for(x = 0; x < BOARD_WIDTH; x++)

			/* Each time player token found, increment value */
			if (board[x][y] == token) 
				tokenCount = tokenCount + 1;
		
	/* return quantity value of tokens to caller */	
	return tokenCount;
}

/* SWAP PLAYER TURN */
/* Swaps both player pointers so that first points to second and vice versa.*/
void swapPlayers(Player ** first, Player ** second)
{
	/* Declare player pointer that acts as a temporary variable */
	/* Then assign the first pointer to the temporary variable */
	Player * playerTemp = *first;

	/* Assign the second pointer to the first pointer */
	*first = *second;

	/* Assign the original pointer for first to second */
	/* This will complete the swap between first and second pointer */
	*second = playerTemp;
}
