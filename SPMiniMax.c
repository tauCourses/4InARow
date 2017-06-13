#include "SPMiniMax.h"

int spMinimaxSuggestMove(SPFiarGame* currentGame, unsigned int maxDepth)
{
	if(currentGame == NULL || maxDepth <= 0)
		return -1;
	if(spFiarCheckWinner(currentGame) != '\0') //if there is already a winner or it's tie
		return -1;

	int values[SP_FIAR_GAME_N_COLUMNS];
	SPFiarGame *copy = spFiarGameCopy(currentGame);
	//decide the mode, if it's the first player it need to be MAX_EVAL, else MIN_EVAL
	//the reason for it is that the scoring function return positive score when the first plyaer in adventage
	evaluationMode mode = (copy->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) ? MAX_EVAL : MIN_EVAL;

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
	return limitValueIndex(values,mode);
}