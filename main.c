#include "main.h"

int main()
{
	SPCommand command;
	SPFiarGame *game = initalize();
	if(game == NULL)
		return -1;
	
	do{
		command = getCommand(game);
		executeCommand(command,&game);
	}while(command.cmd != SP_QUIT);//while user hasn't ended the game
	
	spFiarGameDestroy(game);	
	return 1;
}
