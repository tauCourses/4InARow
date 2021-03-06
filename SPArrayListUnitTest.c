#include "unit_test_util.h"
#include "SPArrayList.h"
#include <stdbool.h>

#define CAPACITY_SIZE 10

static bool spArrayListBasicGetTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddLast(list, i) == SP_ARRAY_LIST_SUCCESS);
	}
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListGetAt(list, i) == i);
	}
	spArrayListDestroy(list);
	return true;
}

static bool spArrayListBasicRemoveTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_SUCCESS);
	}
	ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListRemoveFirst(list) == SP_ARRAY_LIST_SUCCESS);
		ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE - i - 1);
	}
	ASSERT_TRUE(spArrayListIsEmpty(list));
	spArrayListDestroy(list);
	return true;
}

static bool spArrayListBasicAddTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_SUCCESS);
		ASSERT_TRUE(spArrayListSize(list) == i + 1);
	}
	ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE);
	spArrayListDestroy(list);
	return true;
}

static bool spArrayListCreateTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);
	spArrayListDestroy(list);

	list = spArrayListCreate(0);
	ASSERT_TRUE(list == NULL);
	spArrayListDestroy(list);

	list = spArrayListCreate(-5);
	ASSERT_TRUE(list == NULL);
	spArrayListDestroy(list);

	return true;
}

static bool spArrayListCopyTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_SUCCESS);
	}
	SPArrayList* copyList = spArrayListCopy(list);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListGetAt(copyList, i) == spArrayListGetAt(list, i));
	}
	spArrayListDestroy(list);
	spArrayListDestroy(copyList);
	
	copyList = spArrayListCopy(NULL);
	ASSERT_TRUE(copyList==NULL);
	spArrayListDestroy(copyList);
	
	
	return true;
}

static bool spArrayListClearTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_SUCCESS);
	}
	ASSERT_TRUE(spArrayListClear(list) == SP_ARRAY_LIST_SUCCESS);
	ASSERT_TRUE(spArrayListIsEmpty(list));
	spArrayListDestroy(list);
	
	ASSERT_TRUE(spArrayListClear(NULL) == SP_ARRAY_LIST_INVALID_ARGUMENT);
	
	return true;
}

static bool spArrayListStackTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < CAPACITY_SIZE*2; i++) {
		ASSERT_TRUE(spArrayListPush(list, 0) == SP_ARRAY_LIST_SUCCESS);
	}
	ASSERT_TRUE(spArrayListPop(list) == 0);
	ASSERT_TRUE(spArrayListPush(list, 1) == SP_ARRAY_LIST_SUCCESS);
	ASSERT_TRUE(spArrayListPush(list, 1) == SP_ARRAY_LIST_SUCCESS);

	ASSERT_TRUE(spArrayListPop(list) == 1);
	ASSERT_TRUE(spArrayListPop(list) == 1);

	for (int i = 0; i < CAPACITY_SIZE-2; i++) {
		ASSERT_TRUE(spArrayListPop(list) == 0);
	}
	ASSERT_TRUE(spArrayListIsEmpty(list));
	spArrayListDestroy(list);
	
	ASSERT_TRUE(spArrayListClear(NULL) == SP_ARRAY_LIST_INVALID_ARGUMENT);
	
	return true;
}

int main() {
	RUN_TEST(spArrayListCreateTest);
	RUN_TEST(spArrayListCopyTest);
	RUN_TEST(spArrayListClearTest);
	RUN_TEST(spArrayListStackTest);
	
	RUN_TEST(spArrayListBasicAddTest);
	RUN_TEST(spArrayListBasicRemoveTest);
	RUN_TEST(spArrayListBasicGetTest);
	return 0;
}
