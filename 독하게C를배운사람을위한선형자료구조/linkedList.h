#pragma once
#include "error.h"

typedef struct USERDATA {
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pPrev;
	struct USERDATA* pNext;
} USERDATA;


void AddNewNodeAtTail(USERDATA* pTail, int age, char* pszName, char* pszPhone);
void InitList(USERDATA* pHead, USERDATA* pTail);
void ReleaseList(USERDATA* pHead, USERDATA* pTail);
ERROR_CODE RemoveByName(USERDATA* pHead, const char* pszName);
const USERDATA* SearchByName(const USERDATA* pHead, const char* pszName);

void NodeDataCopy(USERDATA* pLeft, USERDATA* pRight);
void SwapNode(USERDATA* pLeft, USERDATA* pRight);
ERROR_CODE SortListByName(USERDATA* pHead, USERDATA* pTail);
ERROR_CODE SortListByAge(USERDATA* pHead, USERDATA* pTail);

void** SearchByIndexAgeRange(USERDATA* pHead, size_t* cnt, int min, int max);