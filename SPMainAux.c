#include "SPMainAux.h"

SPFiarGame* initalize()
{
	unsigned int difficulty = getDifficulty();
	if(difficulty == 0)
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
		scanf("%s",input);
		if (spParserIsInt(input))
		{
			int difficulty = atoi(input); 
			if (difficulty >= 1 && difficulty <= 7)
				return difficulty;
		}
		else if(spParserPraseLine(input).cmd == SP_QUIT)
			break;
		
		printf(ERR_INVALID_LEVEL);
	}
	return 0;
}

SPCommand getCommandFromUser()
{
	char input[SP_MAX_LINE_LENGTH];
	fgets(input,SP_MAX_LINE_LENGTH,stdin);
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
			printf(ERR_INVALID_COMMAND);
		else
			return command;
		
	}
}

bool isGameOverCommand(SPCommand command)
{
	if(command.cmd == SP_QUIT || command.cmd == SP_RESTART)
		return true;
	return false;
}

void executeCommand(SPCommand command,SPFiarGame *game)
{
	switch(command.cmd)
	{
		case SP_UNDO_MOVE:
			executeUndo(game);
			break;
		case SP_ADD_DISC:
			if (!command.validArg)
				printf(ERR_FUNC_FAIL,"main");
			else
				executeAddDisc(command, game);
			break;
		case SP_SUGGEST_MOVE:
			printf(MSG_SUGGEST_MOVE,spMinimaxSuggestMove(game,game->difficulty)+1); //from zero base index to 1 base index
			break;
		case SP_QUIT:
			printf(MSG_EXIT);
			break;
		case SP_RESTART:
			spFiarGameDestroy(game);
			game = initalize();
			break;
		default:
			break;
	}
}

void executeUndo(SPFiarGame *game)
{
	int toRemove = spArrayListGetFirst(game->history);
	if (doOneUndo(game) == -1)
		return;
	else
		printf(MSG_REMOVE_COM_DISC,toRemove);

	toRemove = spArrayListGetFirst(game->history);
	if (doOneUndo(game) == -1)
		return;
	else
		printf(MSG_REMOVE_USER_DISC,toRemove);
}

int doOneUndo(SPFiarGame *game)
{
	SP_FIAR_GAME_MESSAGE gameMessage = spFiarGameUndoPrevMove(game);
	if(gameMessage == SP_FIAR_GAME_INVALID_ARGUMENT)//undo computer move
	{
		printf(ERR_FUNC_FAIL,"main");
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
			printf(ERR_FUNC_FAIL,"main");
		return;
	}
	else if(gameMessage == SP_FIAR_GAME_INVALID_MOVE)
	{	
		printf(ERR_COLUMN_FULL);
		return;
	}
	printf("dss");
	//After user turn is done
	char winner = spFiarCheckWinner(game);
	if(winner != '\0')
	{
		printWinner(winner);
		game->isOver = true;
		return;
	}

	computerTurn(game);
}


void computerTurn(SPFiarGame *game)
{
	spFiarGameSetMove(game,1+spMinimaxSuggestMove(game,game->difficulty));//convert from 0-6 columns to 1-7 columns
	char winner = spFiarCheckWinner(game);
	if(winner != '\0')
	{
		printWinner(winner);
		game->isOver = true;
		return;
	}
	spFiarGamePrintBoard(game);
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
