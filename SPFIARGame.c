#include "SPFIARGame.h"

SPFiarGame* spFiarGameCreate(int historySize)
{
	SPFiarGame* game = (SPFiarGame*) calloc(1,sizeof(SPFiarGame));
	if(game == NULL)
		NULL; 

	memset(game->gameBoard, SP_FIAR_GAME_EMPTY_ENTRY, sizeof(game->gameBoard));
	game->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;

	game->history = spArrayListCreate(historySize);
	if(game->history == NULL)
	{
		free(game);
		return NULL;
	}
	return game;
}

char spFiarGameChangePlayer(char player)
{
	if(player == SP_FIAR_GAME_PLAYER_1_SYMBOL)
		return SP_FIAR_GAME_PLAYER_2_SYMBOL;
	return SP_FIAR_GAME_PLAYER_1_SYMBOL;
}

SPFiarGame* spFiarGameCopy(SPFiarGame* src)
{
	if(src == NULL)
		return NULL;
	SPFiarGame* game = (SPFiarGame*) calloc(1,sizeof(SPFiarGame));
	if(game == NULL)
		NULL; 
	memcpy(game->gameBoard,src->gameBoard,sizeof(src->gameBoard));
	memcpy(game->tops,src->tops,sizeof(src->tops));
	game->currentPlayer = src->currentPlayer;
	game->history = spArrayListCopy(src->history);
	if(game->history == NULL)
	{
		free(game);
		return NULL;
	}
	return game;

}

void spFiarGameDestroy(SPFiarGame* src)
{
	if(src == NULL)
		return;
	spArrayListDestroy(src->history);
	free(src);
}

SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, int col)
{
	if(src == NULL || col<0 || col >= SP_FIAR_GAME_N_COLUMNS)
		return SP_FIAR_GAME_INVALID_ARGUMENT;

	if(src->tops[col] >= SP_FIAR_GAME_N_ROWS)
		return SP_FIAR_GAME_INVALID_MOVE;

	src->gameBoard[src->tops[col]][col] = src->currentPlayer;
	src->currentPlayer = spFiarGameChangePlayer(src->currentPlayer); 
	spArrayListPush(src->history,col);
	src->tops[col]++;
	return SP_FIAR_GAME_SUCCESS;
}

bool spFiarGameIsValidMove(SPFiarGame* src, int col)
{
	if(src == NULL || col<0 || col >= SP_FIAR_GAME_N_COLUMNS)
		return false;

	if(src->tops[col] >= SP_FIAR_GAME_N_ROWS)
		return false;

	return true;
}

SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src)
{
	if(src == NULL)	
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	if(spArrayListIsEmpty(src->history))
		return SP_FIAR_GAME_NO_HISTORY;
	
	int col = spArrayListPop(src->history);
	if(col == -1)
		return SP_FIAR_GAME_NO_HISTORY;
	src->gameBoard[src->tops[col]][col] = SP_FIAR_GAME_EMPTY_ENTRY;
	src->currentPlayer = spFiarGameChangePlayer(src->currentPlayer);
	src->tops[col]--;
		
	return SP_FIAR_GAME_SUCCESS;
}

SP_FIAR_GAME_MESSAGE spFiarGamePrintBoard(SPFiarGame* src)
{
	if(src == NULL)
		return SP_FIAR_GAME_INVALID_ARGUMENT;

	for(int i=SP_FIAR_GAME_N_ROWS - 1; i>=0;i--)
	{
		printf("| ");
		for(int j=0;j<SP_FIAR_GAME_N_COLUMNS;j++)
			printf("%c ", src->gameBoard[i][j]);
		printf("|\n");
	}
	for(int i=0;i<SP_FIAR_GAME_N_COLUMNS*2 + 3; i++)
		printf("-");
	printf("\n  ");
	for(int j=1;j<=SP_FIAR_GAME_N_COLUMNS;j++)
		printf("%d ", j);
	printf(" \n");
	return SP_FIAR_GAME_SUCCESS;
}

char spFiarGameGetCurrentPlayer(SPFiarGame* src)
{
	if(src == NULL)
		return SP_FIAR_GAME_EMPTY_ENTRY;
	return src->currentPlayer;
}

char spFiarCheckWinner(SPFiarGame* src)
{
	if(src == NULL)
		return '\0';

	char val = spFiarCheckPattern(src,0,0,SP_FIAR_GAME_N_ROWS,SP_FIAR_GAME_N_COLUMNS + 1 - SP_FIAR_GAME_SPAN,0,1);
	if(val != '\0')
		return val;

	val = spFiarCheckPattern(src,0,0,SP_FIAR_GAME_N_ROWS + 1-SP_FIAR_GAME_SPAN,SP_FIAR_GAME_N_COLUMNS,1,0);
	if(val != '\0')
		return val;

	val = spFiarCheckPattern(src,0,0,SP_FIAR_GAME_N_ROWS+1-SP_FIAR_GAME_SPAN,SP_FIAR_GAME_N_COLUMNS+1-SP_FIAR_GAME_SPAN,1,1);
	if(val != '\0')
		return val;

	val = spFiarCheckPattern(src,SP_FIAR_GAME_SPAN-1,0,SP_FIAR_GAME_N_ROWS,SP_FIAR_GAME_N_COLUMNS+1-SP_FIAR_GAME_SPAN,-1,1);
	if(val != '\0')
		return val;
	
	for(int i=0; i<SP_FIAR_GAME_N_ROWS;i++)
		for(int j=0;j<SP_FIAR_GAME_N_COLUMNS;j++)
			if(src->gameBoard[i][j] == SP_FIAR_GAME_EMPTY_ENTRY)
				return '\0';
	return SP_FIAR_GAME_TIE_SYMBOL;
}

char spFiarCheckPattern(SPFiarGame* src, int starti, int startj, int endi, int endj, int diri, int dirj)
{
	for(int i=starti; i<endi;i++)
	{
		for(int j=startj;j<endj;j++)
		{
			char val = src->gameBoard[i][j];
			if(val == SP_FIAR_GAME_EMPTY_ENTRY)
				continue;
			for(int k=1;k<SP_FIAR_GAME_SPAN;k++) 
			{
				if(val != spFiarCheckLocation(src,i+diri*k,j+dirj*k))
				{
					val = SP_FIAR_GAME_EMPTY_ENTRY;
					break;
				}
			}
			if(val != SP_FIAR_GAME_EMPTY_ENTRY)
				return val;
		}
	}	
	return '\0';
}

char spFiarCheckLocation(SPFiarGame *src, int i, int j)
{
	if(i<0 || i>=SP_FIAR_GAME_N_ROWS || j<0 || j>=SP_FIAR_GAME_N_COLUMNS)
		return SP_FIAR_GAME_OUT_OF_TABLE;
	return src->gameBoard[i][j];
}

int spFiarUpdateDifficulty(SPFiarGame *src, unsigned int difficulty)
{
	if (src == NULL)
		return -1;
	src->difficulty = difficulty;
	return 1;
}
