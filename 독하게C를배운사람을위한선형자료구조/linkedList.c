#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "linkedList.h"
#include "ui.h"


void AddNewNodeAtTail(USERDATA* pTail, int age, char* pszName, char* pszPhone)
{
 	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	if (pNewNode == NULL) {
		return;
	}
	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
	
	
	pNewNode->pNext = pTail;
	pNewNode->pPrev = pTail->pPrev;
	pTail->pPrev->pNext = pNewNode;
	pTail->pPrev = pNewNode;
} 

void InitList(USERDATA* pHead, USERDATA* pTail)
{
	pHead->pNext = pTail;
	pTail->pPrev = pHead;

	pHead->pPrev = NULL;
	pTail->pNext = NULL;

}


void ReleaseList(USERDATA* pHead, USERDATA* pTail)
{
	pHead = pHead->pNext;
 	while (pHead->pNext != NULL) {
		//printf("삭제: [%p] %d, %s, %s [%p] [%p]\n",
		//	pHead, pHead->age, pHead->name, pHead->phone, pHead->pPrev, pHead->pNext);
		pHead = pHead->pNext;
		free(pHead->pPrev);
	}
	InitList(pHead, pTail);
}




const USERDATA* SearchByName(const USERDATA* pHead, const char* pszName)
{
	pHead = pHead->pNext;
 	while (pHead->pNext != NULL) {
		if (strcmp(pHead->name, pszName) == 0) {
			return pHead;
		}
		pHead = pHead->pNext;
	}
	return NULL;
}

int RemoveByName(USERDATA* pHead, const char* pszName)
{
	USERDATA* pTarget = SearchByName(pHead, pszName);
	if (pTarget == NULL) {
		return INVALID_INPUT;
	}
	pTarget->pPrev->pNext = pTarget->pNext;
	pTarget->pNext->pPrev = pTarget->pPrev;
	/*printf("삭제: [%p] %d, %s, %s [%p] [%p]\n",
		pTarget, pTarget->age, pTarget->name, pTarget->phone, pTarget->pPrev, pTarget->pNext);*/
	free(pTarget);
	return SUCCESS;
}

void NodeDataCopy(USERDATA* pLeft, USERDATA* pRight)
{
	pLeft->age = pRight->age;
	strcpy_s(pLeft->name, sizeof(pLeft->name), pRight->name);
	strcpy_s(pLeft->phone, sizeof(pLeft->phone), pRight->phone);
}
void SwapNode(USERDATA* pLeft, USERDATA* pRight)
{
	USERDATA tmp = *pLeft;
	NodeDataCopy(pLeft, pRight);
	NodeDataCopy(pRight, &tmp);
} 



ERROR_CODE SortListByName(USERDATA* pHead, USERDATA* pTail)
{ // 선택정렬
	if (pHead->pNext == pTail)
		return EMPTY;

	USERDATA* pTmp = pHead->pNext;
	USERDATA* pCmp = NULL;
	USERDATA* pSelected = NULL;
	while (pTmp != pTail->pPrev) {
		pSelected = pTmp;
		pCmp = pTmp->pNext;
		while(pCmp != pTail) {
			if (strcmp(pSelected->name, pCmp->name) > 0) {
				pSelected = pCmp;
			}
			pCmp = pCmp->pNext;
		}

		if (pTmp != pSelected)
			SwapNode(pTmp, pSelected);

		pSelected = NULL;
		pTmp = pTmp->pNext;
	}
	return SUCCESS;

}

ERROR_CODE SortListByAge(USERDATA* pHead, USERDATA* pTail)
{
	if (pHead->pNext == pTail)
		return EMPTY;

	USERDATA* pTmp = pHead->pNext;
	USERDATA* pCmp = NULL;
	USERDATA* pSelected = NULL;
	while (pTmp != pTail->pPrev) {
		pSelected = pTmp;
		pCmp = pTmp->pNext;
		while (pCmp != pTail) {
			if (pSelected->age > pCmp->age) {
				pSelected = pCmp;
			}
			pCmp = pCmp->pNext;
		}

		if (pTmp != pSelected)
			SwapNode(pTmp, pSelected);

		pSelected = NULL;
		pTmp = pTmp->pNext;
	}
	return SUCCESS;
}

void** SearchByIndexAgeRange(USERDATA* pHead, size_t* cnt, int min, int max)
{
	pHead = pHead->pNext;
	USERDATA* pMin = NULL;
	while (pHead->pNext != NULL) {
		if (pHead->age >= min) {
			pMin = pHead;
			break;
		}
		pHead = pHead->pNext;
	}

	if (pMin == NULL)
		return NULL;
	
	while (pHead->pNext != NULL) {
		if (pHead->age > max)
			break;
		++*cnt;
		pHead = pHead->pNext;
	}

	void** pNodePtrList = malloc(sizeof(void*) * *cnt);
	pHead = pMin;
	for (int i = 0; i < *cnt; ++i) {
		pNodePtrList[i] = pMin;
		pMin = pMin->pNext;
	}
	return pNodePtrList;

}