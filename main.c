#include "main.h"
/*
Issues:
1. need to know what is difficulty when exectuting command
2. need to update diffculty on restart
3. need to do quit at ANY point - even in get diffculty
4.

*/
int main()
{
	SPCommand command;
	SPFiarGame *game;

//	int difficulty;
//
//	if((difficulty = getDifficulty()) == -1)
//		return -1;
//	SPFiarGame game = spFiarGameCreate(HISTORY_SIZE);
//	spFiarGamePrintBoard(game);

	game = initalize();
	if (!(game))
		return -1;
	command = getCommand(game);
//	if (!command)
//		return -1;

	while(command.cmd != SP_QUIT)//while user hasn't ended the game
	{
		executeCommand(command,game);
		command = getCommand(game);
		if (!command)
			return -1;
	}
	return 1;
}
