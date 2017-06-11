#include "SPMiniMaxNode.h"

evaluationMode opositeEvaluationMode(evaluationMode mode)
{
	return (evaluationMode) !mode;
}

int modeLimit(evaluationMode mode)
{
	if(mode == MIN_EVAL)
		return INT_MAX
	return INT_MIN;
}

int spMinimaxSuggestNode(SPFiarGame* currentGame, unsigned int maxDepth, evaluationMode mode)
{
	if(maxDepth == 0)
		return scoringFunction(currentGame);
	
	char winner = spFiarCheckWinner(currentGame);
	if(winner == currentGame->currentPlayer)
		return modeLimit(mode);
	else if(winner = spFiarGameChangePlayer(currentGame->currentPlayer))
		return modeLimit(opositeEvaluationMode(mode));

	copy = spFiarGameCopy(currentGame);
	int values[SP_FIAR_GAME_N_COLUMNS];
	
	for(int i=0; i< SP_FIAR_GAME_N_COLUMNS; i++)
	{
		if(!spFiarGameIsValidMove(currentGame,i))
			values[i] = modeLimit(mode);
		else
		{
			spFiarGameSetMove(copy,i);
			values[i] = spMinMaxNode(copy, maxDepth-1, opositeEvaluationMode(mode));
			spFiarGameUndoPrevMove(copy);
		}
	} 
	spFiarGameDestroy(copy);
	
	return values[limitValue(values,mode)];
}

int limitValueIndex(int values[SP_FIAR_GAME_N_COLUMNS], evaluationMode mode)
{
	int limitValue = values[0];
	int limitIndex = 0;
	for(int i=1; i< SP_FIAR_GAME_N_COLUMNS; i++)
	{
		if((mode == MAX_EVAL && values[i] > maxValue) || (mode == MIN_EVAL && values[i] < maxValue))
		{
			limitValue = values[i];
			limitIndex = i;
		}
	}
	return limitIndex;
}

int scoringFunction(SPFiarGame* currentGame)
{
	const int scoreVector = {-5,-2,-1,0,1,2,5};
	int scroing[SCROING_OPTIONS] = {0};
	scoringFunctionPattern(src,0,0,SP_FIAR_GAME_N_ROWS,SP_FIAR_GAME_N_COLUMNS-SP_FIAR_GAME_SPAN,0,1,scroing);
	scoringFunctionPattern(src,0,0,SP_FIAR_GAME_N_ROWS-SP_FIAR_GAME_SPAN,SP_FIAR_GAME_N_COLUMNS,1,0,scroing);
	scoringFunctionPattern(src,0,0,SP_FIAR_GAME_N_ROWS-SP_FIAR_GAME_SPAN,SP_FIAR_GAME_N_COLUMNS-SP_FIAR_GAME_SPAN,1,1,scroing);
	scoringFunctionPattern(src,SP_FIAR_GAME_SPAN,0,SP_FIAR_GAME_N_ROWS,SP_FIAR_GAME_N_COLUMNS-SP_FIAR_GAME_SPAN,-1,1,scroing);

	int finalScore = 0;
	for(int i=0; i<SCROING_OPTIONS; i++)
		finalScore += scoreVector[i]*scroing[i];

	return finalScore;
}

void scoringFunctionPattern(SPFiarGame* currentGame, int starti, int startj, int endi, int endj, int diri, int dirj, int scroing[SCROING_OPTIONS])
{
	for(int i=starti; i<endi;i++)
		for(int j=startj;j<endj;j++)
			scroing[scoringFunctionSpan(currentGame, starti, startj, diri, dirj)]++;
}


int scoringFunctionSpan(SPFiarGame* currentGame, int starti, int startj, int diri, int dirj)
{
	int result = 0;
	for(int i=0;i<SP_FIAR_GAME_EMPTY_ENTRY;i++)
	{
		char temp = spFiarCheckLocation(currentGame, i+diri*k,j+dirj*k);
		if(temp == SP_FIAR_GAME_PLAYER_1_SYMBOL)
			result++;
		else if(temp == SP_FIAR_GAME_PLAYER_2_SYMBOL)
			result--;
	}
	return result;
}