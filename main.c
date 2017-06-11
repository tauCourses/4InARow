#include "main.h"
#include "SPFIARGame.h"
#include "SPFIARParser.h"



int main()
{
	SPCommand command;
	SPFiarGame game;

	if (!(game = initalize()))
		return -1;
	if (!(command = getCommand(game)))
		return -1;

	while(command.cmd != SP_QUIT)//while user hasn't ended the game
	{
		executeCommand(command,game);
		if (!(command = getCommand(game)))
			return -1;
	}
	return 1;
}
