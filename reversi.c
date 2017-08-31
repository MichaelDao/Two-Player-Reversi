#include "reversi.h"

/* INITIAL METHOD */
/* This is where the program starts, menu is initialized here */
int main(void)
{
	Boolean running = TRUE; /* Loop boolean */
	
	/* Begin menu loop */
	do
	{
		/* Print menu */
		printf("\nWelcome to Reversi!\n"
			"===================\n"
			"Select an option:\n"
			"1. Play a game\n"
			"2. Quit the program\n"
			"Please enter your choice: ");

		/* If user inputs 2, stop menu loop */
		if (!readMenuInput())	
			break;

	/* End loop when user exits */
	} while (running);
		
	/* Prompt and terminate program */	
	printf("\nGoodbye.\n\n");	
	return EXIT_SUCCESS;
}

Boolean readMenuInput()
{
	char input[3]; /* menu input */
	Player first, second; /* Player structures defined for players */
	Player * winner; /* This is what playGame() will return */

	/* Read user input */
	fgets(input, sizeof(input), stdin);	 
	
	/* Prevent buffer overflow */	
 	if (strlen(input) > sizeof(input) || input[strlen(input)-1] != '\n')
	{
		readRestOfLine();
		/* Repeat menu loop */ 
		return TRUE;
	}
		
	/* Requre this to prevent buffer overflow from stopping input */
	input[strcspn(input,"\n")] = '\0';		
	
	/* If user inputs '1', call game.c */
	if (strcmp(input, "1") == 0)
	{
		/* Call playGame method and return winner */
		winner = playGame(&first, &second);
		
		if (winner == NULL)
			/* Draw if there is no winner */
			printf("\nThere has been a draw!\n");
		else 
			/* Print name and score of the winner */
			printf("\n%s has won with %d tokens!\n",
				winner->name, winner->score);
	}

	/* Stop the menu loop and end the program */
	else if (strcmp(input, "2") == 0)
		return FALSE;
	
	/* Repeat the menu loop */
	return TRUE;
}
