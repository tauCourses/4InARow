#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

#include <limits.h>
#include "SPFIARGame.h"
#include "SPMiniMax.h"

#define SCORING_OPTIONS 7
typedef enum {MAX_EVAL, MIN_EVAL} evaluationMode;

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
int modeWorstValueLimit(evaluationMode mode);
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

/**
 * calc the score of the current situation
 * @param currentGame - the current game needed to evaluate
 * @return - the score according to what we had to implement
 */
int scoringFunction(SPFiarGame* currentGame);

/**
 * check a specific pattern and update the scroing vector
 * @param currentGame - the current game
 * @param starti, startj - the start point of the area to check the pattern
 * @param endi, endj - the end point of the area to check the pattern
 * @param diri, dirj - the direction of the pattern
 * @param scoring[SCORING_OPTIONS] - an array of integers represent the scoring vector
 */
void scoringFunctionPattern(SPFiarGame* currentGame, int starti, int startj, int endi, int endj, int diri, int dirj, int scoring[SCORING_OPTIONS]);

/**
 * check a specific span and return the value of the span
 * @param currentGame - the current game
 * @param starti,startj - the start point of the span
 * @param diri, dirj - the direction of the pattern
 * @return - the number of SP_FIAR_GAME_PLAYER_1_SYMBOL - the number of SP_FIAR_GAME_PLAYER_2_SYMBOL
 */
int scoringFunctionSpan(SPFiarGame* currentGame, int starti, int startj, int diri, int dirj);

#endif
