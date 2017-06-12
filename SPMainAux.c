#include "SPMainAux.h"
#include "main.h"


SPFiarGame* initalize()
{
	unsigned int difficulty;
	if((difficulty = getDifficulty()) == -1)
		return NULL;
	SPFiarGame* game = spFiarGameCreate(HISTORY_SIZE,difficulty);
	spFiarGamePrintBoard(game);
	spFiarUpdateDifficulty(game,difficulty);
	return game;
}

unsigned int getDifficulty()
{
	char *input;
	bool validInput = false;
	int difficulty;
	while (!validInput)
	{
		printf(MSG_ENTER_DIFF_LEVEL);
			if(!gets(input))
			{
				printf(ERR_FUNC_FAIL,"getDifficulty");
				return -1;
			}
			if (spParserIsInt(input))
			{
				if ((difficulty < 1) | (difficulty > 7))
				{
					printf(ERR_INVALID_LEVEL);
				}
				else
				{
					validInput = true;
					return (atoi(input)+UINT_MAX+1);//the int number converted to an unsigned int
				}
			}
			else
			{
				if (spParserPraseLine(input).cmd == SP_QUIT)
					return -1;
				else
					printf(ERR_INVALID_LEVEL);
			}
	}
	printf(ERR_FUNC_FAIL,"getDifficulty");
	return -1;
}





SPCommand getCommand(SPFiarGame game)
{
	SPCommand command = malloc(sizeOf(SPCommand));
	char *input;
	if (spFiarCheckWinner(game))
	{
		if (!(command = getGameOverCommand()()))
			return NULL;
	}
	else
	{
		printf(MSG_NEXT_MOVE);
		gets(input);
		if(!gets(input))
		{
			printf(ERR_FUNC_FAIL,"getCommand");
			command.validArg = false;
			return command;
		}
		return spParserPraseLine(input);
	}
	command.validArg = false;
	return command;

}

SPCommand getGameOverCommand()
{
	char *input;
	gets(input);
	SPCommand command = malloc(sizeOf(SPCommand));
	if(!gets(input))
	{
		printf(ERR_FUNC_FAIL,"getGameOverCommand");
		return NULL;
	}
	command = spParserPraseLine(input);
	while ((command.cmd != SP_QUIT) && (command.cmd != SP_RESTART))
	{
		printf(ERR_INVALID_COMMAND);
		if(!gets(input))
		{
			printf(ERR_FUNC_FAIL,"getGameOverCommand");
			return NULL;
		}
		command = spParserPraseLine(input);
	}
	return command;
}

int executeCommand(SPCommand command,SPFiarGame game)
{
	switch (command.cmd)
		{
			case (SP_UNDO_MOVE):
					executeUndo(game);
					break;
			case (SP_ADD_DISC):
					executeAddDisc(command, game,game->difficulty);
					break;
			case (SP_SUGGEST_MOVE):
					printf(MSG_SUGGEST_MOVE,1+spMinimaxSuggestMove(game,game->difficulty));
					break;
			case (SP_QUIT):
					printf(MSG_EXIT);
					spFiarGameDestroy(game);
					break;
			case (SP_RESTART):
					spFiarGameDestroy(game);
					game = initalize();
					break;
					//return 2;
		}
	return 1;
}

void executeUndo(SPFiarGame game)
{
	int toRemove = spArrayListGetFirst(game);
	if (doOneUndo(game) == -1)
		return;
	else
		printf(MSG_REMOVE_COM_DISC,toRemove);

	toRemove = spArrayListGetFirst(game);
	if (doOneUndo(game) == -1)
		return;
	else
		printf(MSG_REMOVE_USER_DISC,toRemove);
}

int doOneUndo(SPFiarGame game)
{
	SP_FIAR_GAME_MESSAGE gameMessage;
	int toRemove = SPArrayListPeek(game);
	if ((gameMessage = spFiarGameUndoPrevMove(game)) == SP_FIAR_GAME_INVALID_ARGUMENT)//undo computer move
	{
		printf(ERR_FUNC_FAIL,"main");
		return -1;
	}

	else
	{
		if (gameMessage == SP_FIAR_GAME_NO_HISTORY)
		{
			printf(ERR_CANNOT_UNDO);
			return -1;
		}
	}
	return 1;

}

void executeAddDisc(SPCommand command,SPFiarGame game,int difficulty)
{
	SP_FIAR_GAME_MESSAGE gameMessage;
	if (!command.validArg)
			printf(ERR_FUNC_FAIL,"main");
			return;
	if ((gameMessage = spFiarGameSetMove(game,command.arg)) == SP_FIAR_GAME_INVALID_ARGUMENT)
	{
		if ((command.arg > 7)|(command.arg < 1))
			printf(ERR_COLUMN_OUT_OF_RANGE);
		else //if game == null
			printf(ERR_FUNC_FAIL,"main");
		return;
	}
	if ((gameMessage = spFiarGameSetMove(game,command.arg)) == SP_FIAR_GAME_INVALID_MOVE)
	{
		printf(ERR_COLUMN_FULL);
		return;
	}

	//after user turn is done
	if (spFiarCheckWinner(game))
		printWinner(game);
	else
	{
		computerTurn(game);
		if (spFiarCheckWinner(game))
			printWinner(game);
		else			{
		{
			spFiarGamePrintBoard(game);
		}
	}
}


void computerTurn(SPFiarGame game)
{
	spFiarGameSetMove(game,1+spMinimaxSuggestMove(game,game->difficulty));//convert from 0-6 columns to 1-7 columns
}



void printWinner(SPFiarGame game)
{
	char winner = spFiarCheckWinner(game);
	if (winner == SP_FIAR_GAME_PLAYER_1_SYMBOL)
		printf(MSG_YOU_WIN);
	else
	{
		if (winner == SP_FIAR_GAME_PLAYER_2_SYMBOL)
			printf(MSG_COM_WIN);
		else
			printf(MSG_TIE);
	}
}
