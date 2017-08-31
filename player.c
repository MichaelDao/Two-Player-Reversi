#include"player.h"
#include "time.h"

/* INITIALIZE PLAYER ONE */
/* Randomly assign a token colour to this player */
/* Initialize everything else for player one */
void initFirstPlayer(Player * player)
{	
	/* variable for randomizer */
	int randomNumber;

	/* Seed the rand() function) */	
	srand(time(NULL));

	/* random integer between 0 and 100 */
	randomNumber = rand() % 100 ;

	/* If random number is odd = RED, if even = CYAN */
	if (randomNumber % 2) 
		player->token = RED;
	else 
		player->token = CYAN;

	/* Initialize score */
	player->score = 0;

	/* Start validating name input */
	for(;;)
	{
		/* Prompt for input */
		printf("\nPlease enter the first player's name: ");
	
		/* Validate the player name, break loop if valid */
		if(validateName(player))
			break;
	}
	/* Clear newline after the input */
	player->name[strcspn(player->name,"\n")] = '\0';
}

/* INITIALIZE PLAYER TWO */
/* Assign the opposite colour to player one */
/* Initialize everything relevant to player two */
void initSecondPlayer(Player * player, Cell token)
{
	/* Set token color opposite to player one */
	if (token == RED)
		player->token = CYAN;
	else 
		player->token = RED;

	/* Initialize score */
	player->score = 0;

	/* Start validating name input */
	for(;;)
	{
		/* Prompt for input */
		printf("Please enter the second player's name: ");
		
		/* Validate the player name, break loop if valid */
		if(validateName(player))
			break;
	}
	/* Clear newline after the input */
	player->name[strcspn(player->name,"\n")] = '\0';
} 

/* VALIDATE NAME INPUT */
/* Validate the name input, prevent buffer overflow */
Boolean validateName(Player * player)
{
	/* Capture input */
	fgets(player->name, sizeof(player->name), stdin);		

	/* This will detect buffer overflow */
	if (player->name[strlen(player->name) - 1] != '\n') 
	{	
		printf("\noverflow, please enter your name again!\n");
		readRestOfLine();
	}

	/* This will ensure that the size of name is within range */
	else if (strlen(player->name) > sizeof(player->name))
	{
		printf("\noverflow, please enter your name again\n");
		readRestOfLine();
	}

	/* If the input is blank, prompt for name again */
	else if (strlen(player->name) <= NULL_SPACE)
		printf("\nPlease enter something!\n");
	
	/* Break loop in calling method if valid */
	else
		return TRUE;
	
	/* Do not break loop in calling method if not valid */
	return FALSE;
}

/* PRINT PLAYER DETAILS */
/* Print the details of both player one and two before gameboard */
void printPlayerDetail(Player * first, Player * second) 
{
	int z; /* Index used to print lines */

	/* Print borderline */
	for (z = 0; z < 80; z++)
		printf("=");

 	/* Print Player One details */
	printf("\nPlayer One's Details\n" "--------------------\n"
		"Name: %s \tScore: %d \tToken Color: ",
		 first->name, first->score);

	/* Print the correct token colour for player 1 */
	if (first->token == RED)
		/* RED token */
		printf("%s0%s\n", COLOR_RED, COLOR_RESET);
	else
		/* CYAN token */
		printf("%s0%s\n", COLOR_CYAN, COLOR_RESET);

	/* Print line */
 	for (z = 0; z < 80; z++)
		printf("-");
		
	/* Print Player two details */
	printf("\nPlayer Two's Details\n" "--------------------\n"
		"Name: %s \tScore: %d \tToken Color: ", second->name,
		 second->score);	

	/* Print correct token colour for player 2 */
	if (second->token == RED)
		/* RED token */
		printf("%sO%s\n", COLOR_RED, COLOR_RESET);
	else
		/* CYAN token */
		printf("%sO%s\n", COLOR_CYAN, COLOR_RESET);

	/* Print line */
	for (z = 0; z < 80; z++)
		printf("-");
}
