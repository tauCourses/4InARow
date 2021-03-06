#include "SPMiniMaxNode.h"

evaluationMode opositeEvaluationMode(evaluationMode mode)
{
	return (evaluationMode) !mode;
}

int modeWorstValueLimit(evaluationMode mode)
{
	if(mode == MIN_EVAL)
		return INT_MAX;
	return INT_MIN;
}

int spMinimaxSuggestNode(SPFiarGame* currentGame, unsigned int maxDepth, evaluationMode mode)
{	
	char winner = spFiarCheckWinner(currentGame); //check if the game is over
	if(winner == SP_FIAR_GAME_PLAYER_1_SYMBOL)
		return INT_MAX - 100; //need to be still better than a full column
	else if(winner == SP_FIAR_GAME_PLAYER_2_SYMBOL)
		return INT_MIN + 100; //need to be still better than a full column
	else if(winner == SP_FIAR_GAME_TIE_SYMBOL)
		return 0;

	if(maxDepth == 0)
		return scoringFunction(currentGame);
	
	SPFiarGame *copy = spFiarGameCopy(currentGame);
	int values[SP_FIAR_GAME_N_COLUMNS];
	
	for(int i=0; i< SP_FIAR_GAME_N_COLUMNS; i++)
	{
		if(!spFiarGameIsValidMove(currentGame,i))
			values[i] = modeWorstValueLimit(mode);
			
		else
		{	
			spFiarGameSetMove(copy,i);
			values[i] = spMinimaxSuggestNode(copy, maxDepth-1, opositeEvaluationMode(mode));
			spFiarGameUndoPrevMove(copy);
		}
	} 
	spFiarGameDestroy(copy);
	return values[limitValueIndex(values,mode)];
}

int limitValueIndex(int values[SP_FIAR_GAME_N_COLUMNS], evaluationMode mode)
{
	int limitValue = values[0];
	int limitIndex = 0;
	for(int i=1; i< SP_FIAR_GAME_N_COLUMNS; i++)
	{
		if((mode == MAX_EVAL && values[i] > limitValue) || (mode == MIN_EVAL && values[i] < limitValue))
		{
			limitValue = values[i];
			limitIndex = i;
		}
	}
	return limitIndex;
}

int scoringFunction(SPFiarGame* currentGame)
{
	const int scoreVector[] = 		{-5,-2,-1, 0, 1, 2, 5};
	int scoring[SCORING_OPTIONS] = 	{0 , 0, 0, 0, 0, 0, 0};
	scoringFunctionPattern(currentGame,0,0,SP_FIAR_GAME_N_ROWS,SP_FIAR_GAME_N_COLUMNS+1-SP_FIAR_GAME_SPAN,0,1,scoring);	
	scoringFunctionPattern(currentGame,0,0,SP_FIAR_GAME_N_ROWS+1-SP_FIAR_GAME_SPAN,SP_FIAR_GAME_N_COLUMNS,1,0,scoring);
	scoringFunctionPattern(currentGame,0,0,SP_FIAR_GAME_N_ROWS+1-SP_FIAR_GAME_SPAN,SP_FIAR_GAME_N_COLUMNS+1-SP_FIAR_GAME_SPAN,1,1,scoring);
	scoringFunctionPattern(currentGame,SP_FIAR_GAME_SPAN-1,0,SP_FIAR_GAME_N_ROWS,SP_FIAR_GAME_N_COLUMNS+1-SP_FIAR_GAME_SPAN,-1,1,scoring);
	
	int finalScore = 0;
	for(int i=0; i<SCORING_OPTIONS; i++)
		finalScore += scoreVector[i]*scoring[i];

	return finalScore;
}

void scoringFunctionPattern(SPFiarGame* currentGame, int starti, int startj, int endi, int endj, int diri, int dirj, int scoring[SCORING_OPTIONS])
{
	for(int i=starti; i<endi;i++)
		for(int j=startj;j<endj;j++)
			scoring[scoringFunctionSpan(currentGame, i, j, diri, dirj)+3]++;
}


int scoringFunctionSpan(SPFiarGame* currentGame, int starti, int startj, int diri, int dirj)
{
	int result = 0;
	for(int k=0;k<SP_FIAR_GAME_SPAN;k++)
	{
		char temp = spFiarCheckLocation(currentGame, starti+diri*k,startj+dirj*k);
		if(temp == SP_FIAR_GAME_PLAYER_1_SYMBOL)
			result++;
		else if(temp == SP_FIAR_GAME_PLAYER_2_SYMBOL)
			result--;
	}

	return result;
}