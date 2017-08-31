reversi: game.c gameboard.c reversi.c player.c utility.c
	gcc -ansi -pedantic -Wall -o compiledGame game.c gameboard.c reversi.c player.c utility.c -I.
