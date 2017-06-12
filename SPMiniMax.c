#include "SPMiniMax.h"

int spMinimaxSuggestMove(SPFiarGame* currentGame, unsigned int maxDepth)
{
	if(currentGame == NULL || maxDepth <= 0)
		return -1;
	if(spFiarCheckWinner(currentGame) != '\0') //if there is already a winner or it's tie
		return -1;

	int values[SP_FIAR_GAME_N_COLUMNS];
	SPFiarGame *copy = spFiarGameCopy(currentGame);
	evaluationMode mode = (copy->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) ? MAX_EVAL : MIN_EVAL;
	printf("\nmode - %d\n\n", mode);
	for(int i=0; i< SP_FIAR_GAME_N_COLUMNS; i++)
	{
		if(!spFiarGameIsValidMove(currentGame,i))
			values[i] = modeWorstValueLimit(mode);
		else
		{
			spFiarGameSetMove(copy,i);
			values[i] = spMinimaxSuggestNode(copy, maxDepth-1, opositeEvaluationMode(mode));
			printf("%d - %d\n", i, values[i]);
			spFiarGameUndoPrevMove(copy);
		}
	} 
	
	spFiarGameDestroy(copy);
	return limitValueIndex(values,mode);
}