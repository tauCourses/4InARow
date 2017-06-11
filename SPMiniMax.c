
int spMinimaxSuggestMove(SPFiarGame* currentGame, unsigned int maxDepth)
{
	if(currentGame == NULL || maxDepth == 0)
		return -1
	int values[SP_FIAR_GAME_N_COLUMNS];
	copy = spFiarGameCopy(currentGame);
	evaluationMode mode = (copy->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) ? MAX_EVAL : MIN_EVAL;

	for(int i=0; i< SP_FIAR_GAME_N_COLUMNS; i++)
	{
		if(!spFiarGameIsValidMove(currentGame,i))
			values[i] = modeLimit(mode);;
		else
		{
			spFiarGameSetMove(copy,i);
			values[i] = spMinimaxSuggestNode(copy, maxDepth-1, mode);
			spFiarGameUndoPrevMove(copy);
		}
	} 
	
	spFiarGameDestroy(copy);
	return limitValueIndex(values,mode);
}