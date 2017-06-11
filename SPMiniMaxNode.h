#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

#include <limits.h>
#include "SPFIARGame.h"

#define SCROING_OPTIONS 9
enum evaluationMode {MAX_EVAL, MIN_EVAL};

/**
 * return the oposite mode
 * @param mode - the current mode
 * @return: (mode==MIN_EVAL) => MAX_EVAL, otherwise - MIN_EVAL
 */
evaluationMode opositeEvaluationMode(evaluationMode mode);
/**
 * return the worse value according to the mode
 * @param mode - the current mode
 * @return: (mode==MIN_EVAL) => INT_MAX, otherwise - INT_MIN
 */
int modeLimit(evaluationMode mode);
/**
 * Given a game state, this function return the score of the  best move according to
 * mode. The current game state doesn't change
 * by this function including the history of previous moves.
 *
 * @param currentGame - The current game state
 * @param maxDepth - The maximum depth of the miniMax algorithm
 * @param mode - MIN/MAX mode
 * @return
 * the score if the position, according to the mode
 * if currentGame is NULL it's undefined
 */
int spMinimaxSuggestNode(SPFiarGame* currentGame, unsigned int maxDepth, evaluationMode mode);

/**
 * return the MAX/MIN index according to the mode
 * @param values - an array of ints that represent the value of add a coin to each column
 * @param mode - indicate if to return the MAX value index or the MIN value index
 * @return - the index of the value in the limit according to the mode
 * if two values are the same, return the lower index
 */
int limitValueIndex(int values[SP_FIAR_GAME_N_COLUMNS], evaluationMode mode);

int scoringFunction(SPFiarGame* currentGame);

void scoringFunctionPattern(SPFiarGame* currentGame, int starti, int startj, int endi, int endj, int diri, int dirj, int scroing[SCROING_OPTIONS]);

int scoringFunctionSpan(SPFiarGame* currentGame, int starti, int startj, int diri, int dirj);

#endif
