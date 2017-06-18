#include "SPMainAux.h"

SPFiarGame* initalize()
{
	unsigned int difficulty = getDifficulty();
	if(difficulty == 0)//'quit' was entered by user or error occurred
		return NULL;
	SPFiarGame* game = spFiarGameCreate(HISTORY_SIZE);
	spFiarUpdateDifficulty(game,difficulty);
	spFiarGamePrintBoard(game);
	return game;
}

unsigned int getDifficulty()
{
	char input[SP_MAX_LINE_LENGTH];
	while(1)
	{
		printf(MSG_ENTER_DIFF_LEVEL);
		fgets(input,SP_MAX_LINE_LENGTH,stdin);
		if (input == NULL)//error in fgets
		{
			printf(ERR_FUNC_FAIL, "fgets");
			break;
		}
		if (spParserIsInt(input))
		{
			int difficulty = atoi(input); 
			if (difficulty >= 1 && difficulty <= 7)
				return difficulty;
		}
		else if(spParserPraseLine(input).cmd == SP_QUIT)
		{
			printf(MSG_EXIT);
			break;
		}

		printf(ERR_INVALID_LEVEL);
	}
	return 0;
}

SPCommand getCommandFromUser()
{
	char input[SP_MAX_LINE_LENGTH];
	fgets(input,SP_MAX_LINE_LENGTH,stdin);
	if (input == NULL)//error in fgets
	{
		printf(ERR_FUNC_FAIL, "fgets");
		SPCommand errorCommand;
		errorCommand.cmd = SP_QUIT;
		errorCommand.validArg = true; // marks command as an error
		return errorCommand;
	}
	return spParserPraseLine(input);
}

SPCommand getCommand(SPFiarGame *game)
{
	if(game->isOver)
		printf(MSG_AFTER_GAME_OVER);
	else
		printf(MSG_NEXT_MOVE);

	while(1)
	{
		SPCommand command = getCommandFromUser();
		if(command.cmd == SP_INVALID_LINE)
			printf(ERR_INVALID_COMMAND);		
		else if (game->isOver == 1 && !isGameOverCommand(command))	
			printf(ERR_GAME_OVER);
		else if(command.cmd == SP_UNDO_MOVE && spArrayListIsEmpty(game->history))
			printf(ERR_CANNOT_UNDO);
		else if(command.cmd == SP_ADD_DISC && (command.arg < 1 || command.arg > 7))
			printf(ERR_COLUMN_OUT_OF_RANGE);
		else if(command.cmd == SP_ADD_DISC && !spFiarGameIsValidMove(game, command.arg-1))
			printf(ERR_COLUMN_FULL,command.arg);
		else if(command.cmd == SP_SUGGEST_MOVE)
			printf(MSG_SUGGEST_MOVE,spMinimaxSuggestMove(game,game->difficulty)+1); //from zero base index to 1 base index
		else
			return command;		
	}
}

bool isGameOverCommand(SPCommand command)
{
	if(command.cmd == SP_QUIT || command.cmd == SP_RESTART || command.cmd == SP_UNDO_MOVE)
		return true;
	return false;
}

void executeCommand(SPCommand *command,SPFiarGame **pointerToGame)
{
	SPFiarGame *game = *pointerToGame;
	switch(command->cmd)
	{
		case SP_UNDO_MOVE:
			executeUndo(game);
			break;
		case SP_ADD_DISC:
			if (!command->validArg)
			{
				printf(ERR_FUNC_FAIL,"fgets");
				spFiarGameDestroy(game);
				command->cmd = SP_QUIT;
			}
			else
				executeAddDisc(*command, game);
			break;
		case SP_SUGGEST_MOVE:
			printf(MSG_SUGGEST_MOVE,spMinimaxSuggestMove(game,game->difficulty)+1); //from zero base index to 1 base index
			break;
		case SP_QUIT:
		{
			if (command->validArg == false)//if 'quit' command was entered
				printf(MSG_EXIT);
			else //fgets had an error
				printf(ERR_FUNC_FAIL,"fgets");
			break;
		}

		case SP_RESTART:
			spFiarGameDestroy(game);
			printf(MSG_RESTARTED);
			*pointerToGame = initalize(); // initialize a new game.
			if(*pointerToGame == NULL)//if in initialzition 'quit' was entered.
				{
					command->cmd = SP_QUIT;
					command->validArg = true;
				}

			break;
		default:
			break;
	}
}

void executeUndo(SPFiarGame *game)
{
	int toRemove = spArrayListGetFirst(game->history)+1; //zero base to 1 base array
	if (doOneUndo(game) == -1)
		return;
	else
		printf(MSG_REMOVE_COM_DISC,toRemove);

	toRemove = spArrayListGetFirst(game->history)+1; 
	if (doOneUndo(game) == -1)
		return;
	else
		printf(MSG_REMOVE_USER_DISC,toRemove);

	spFiarGamePrintBoard(game);	
}

int doOneUndo(SPFiarGame *game)
{
	SP_FIAR_GAME_MESSAGE gameMessage = spFiarGameUndoPrevMove(game);
	if(gameMessage == SP_FIAR_GAME_INVALID_ARGUMENT)//undo computer move
	{
		printf(ERR_FUNC_FAIL,"malloc");
		return -1;
	}
	else if (gameMessage == SP_FIAR_GAME_NO_HISTORY)
	{
		printf(ERR_CANNOT_UNDO);
		return -1;
	}
	return 1;
}

void executeAddDisc(SPCommand command,SPFiarGame *game)
{
	SP_FIAR_GAME_MESSAGE gameMessage = spFiarGameSetMove(game,command.arg-1);	
	if(gameMessage == SP_FIAR_GAME_INVALID_ARGUMENT)
	{
		if (command.arg < 1 || command.arg > 7)
			printf(ERR_COLUMN_OUT_OF_RANGE);
		else //if game == null
			printf(ERR_FUNC_FAIL,"malloc");
		return;
	}
	else if(gameMessage == SP_FIAR_GAME_INVALID_MOVE)
	{	
		printf(ERR_COLUMN_FULL, command.arg);
		return;
	}
	//After user turn is done
	char winner = spFiarCheckWinner(game);
	if(winner != '\0')
	{
		printWinner(winner);
		game->isOver = true;
	}
	else
		computerTurn(game);
	spFiarGamePrintBoard(game);
}


void computerTurn(SPFiarGame *game)
{
	int nextMove = spMinimaxSuggestMove(game,game->difficulty);
	printf(MSG_COM_MOVE,nextMove+1);
	spFiarGameSetMove(game,nextMove);
	char winner = spFiarCheckWinner(game);
	if(winner != '\0')
	{
		printWinner(winner);
		game->isOver = true;
		return;
	}
}



void printWinner(char winner)
{
	if (winner == SP_FIAR_GAME_PLAYER_1_SYMBOL)
		printf(MSG_YOU_WIN);
	else if (winner == SP_FIAR_GAME_PLAYER_2_SYMBOL)
		printf(MSG_COM_WIN);
	else
		printf(MSG_TIE);
}

