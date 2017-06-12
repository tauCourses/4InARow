#include "unit_test_util.h"
#include "SPMiniMax.h"
//#include "SPMiniMaxNode.h"
#include <stdbool.h>

#define HISTORY_SIZE 20

static bool opositeEvaluationModeTest()
{
	ASSERT_TRUE(opositeEvaluationMode(MAX_EVAL) == MIN_EVAL);
	ASSERT_TRUE(opositeEvaluationMode(MIN_EVAL) == MAX_EVAL);
	return true;
}

static bool modeWorstValueLimitTest()
{
	ASSERT_TRUE(modeWorstValueLimit(MAX_EVAL) == INT_MIN);
	ASSERT_TRUE(modeWorstValueLimit(MIN_EVAL) == INT_MAX);
	return true;
}

static bool limitValueIndexTest()
{
	int values[SP_FIAR_GAME_N_COLUMNS] = {-1,2,2,6,-4,9,9};
	ASSERT_TRUE(limitValueIndex(values,MAX_EVAL) == 5);
	ASSERT_TRUE(limitValueIndex(values,MIN_EVAL) == 4);
	return true;
}

static bool scoringFunctionTest()
{
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	int val = scoringFunction(res);
	//printf("\n%d\n",val);
	ASSERT_TRUE(val == 0);
	
	spFiarGameSetMove(res,0);
	val = scoringFunction(res);
	//printf("\n%d\n",val);
	ASSERT_TRUE(val == 3);
	
	spFiarGameSetMove(res,0);
	val = scoringFunction(res);
	//printf("\n%d\n",val);
	ASSERT_TRUE(val == -1);

	spFiarGameSetMove(res,1);
	val = scoringFunction(res);
	//printf("\n%d\n",val);
	ASSERT_TRUE(val == 3);
	
	spFiarGameSetMove(res,2);
	val = scoringFunction(res);
	//printf("\n%d\n",val);
	ASSERT_TRUE(val == -2);

	spFiarGameDestroy(res);	
	return true;
}

static bool scoringFunctionTest2()
{
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	
	spFiarGameSetMove(res,1);
	spFiarGameSetMove(res,5);
	spFiarGameSetMove(res,1);
	spFiarGameSetMove(res,1);
	spFiarGameSetMove(res,1);
	spFiarGameSetMove(res,6);
	spFiarGameSetMove(res,1);
	spFiarGameSetMove(res,3);
	spFiarGameSetMove(res,4);
	spFiarGameSetMove(res,3);
	spFiarGameSetMove(res,2);
	spFiarGameSetMove(res,2);
	spFiarGameSetMove(res,3);
	spFiarGameSetMove(res,2);
	
	int val = scoringFunction(res);
	ASSERT_TRUE(val == -6);
	spFiarGameDestroy(res);
	
	return true;
}

static bool spMinimaxSuggestNodeTest() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	
	for(int i=0;i<3;i++)
	{
		spFiarGameSetMove(res,i);
		spFiarGameSetMove(res,i);	
	}
	int val = spMinimaxSuggestNode(res, 5, MAX_EVAL);
	ASSERT_TRUE(val == INT_MAX);
	
	spFiarGameSetMove(res,6);	
	val = spMinimaxSuggestNode(res, 5, MIN_EVAL);
	ASSERT_TRUE(val == -13);
	
	spFiarGameDestroy(res);
	
	return true;
}

int main() {
	RUN_TEST(opositeEvaluationModeTest);
	RUN_TEST(modeWorstValueLimitTest);
	RUN_TEST(limitValueIndexTest);
	RUN_TEST(scoringFunctionTest);
	RUN_TEST(scoringFunctionTest2);
	RUN_TEST(spMinimaxSuggestNodeTest);

	return 0;
}