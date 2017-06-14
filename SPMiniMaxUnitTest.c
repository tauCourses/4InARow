#include "unit_test_util.h"
#include "SPFIARGame.h"
#include "SPMiniMax.h"
#include "SPMiniMaxNode.h"
#include <stdbool.h>
#include <limits.h>

#define HISTORY_SIZE 20

static bool spMinimaxSuggestMoveTest() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	
	for(int i=0;i<3;i++)
	{
		spFiarGameSetMove(res,i);
		spFiarGameSetMove(res,i);	
	}
	int val = spMinimaxSuggestMove(res, 5);
	ASSERT_TRUE(val == 3);
	
	spFiarGameSetMove(res,6);	
	val = spMinimaxSuggestMove(res, 5);
	ASSERT_TRUE(val == 3);
	
	spFiarGameDestroy(res);
	
	return true;
}

static bool spMinimaxSuggestMoveTest2() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	for(int i=0;i<1;i++)
	{
		int val = spMinimaxSuggestMove(res, 7);	
		spFiarGameSetMove(res,val);
	}
	
	spFiarGamePrintBoard(res);
	spFiarGameDestroy(res);
	
	return true;
}

int main() {
	RUN_TEST(spMinimaxSuggestMoveTest);
	RUN_TEST(spMinimaxSuggestMoveTest2);
	return 0;
}