#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "ui.h"


MY_MENU PrintMenu(void)
{
	MY_MENU input = 0;
	system("cls");
	printf("[1]New\t[2]Search\t[3]Print\t[4]Remove\t[5]SortByName\t[0]Exit\n");
	if (1 != scanf_s("%d%*c", &input)) {
		return 0;
	}
	return input;
}
void EventLoopRun(USERDATA* pHead, USERDATA* pTail)
{
	MY_MENU menu = 0;
	int result = 0;
	while ((menu = PrintMenu()) != 0) {
		switch (menu) {
		case NEW:
			result = New(pTail);
			CheckFuncResult(result);
			break;
		case SEARCH:
			result = Search(pHead, pTail);
			CheckFuncResult(result);
			break;
		case PRINT:
			PrintList(pHead);
			break;
		case REMOVE:
			result = Remove(pHead);
			CheckFuncResult(result);
			break;
		case SORT:
			result = Sort(pHead, pTail);
			CheckFuncResult(result);
			break;
		case EXIT:
			return;
		default:
			;
		}
		_getch();
	}
}

void PrintOne(const USERDATA* pElement)
{
	printf("[%p] %d, %s, %s [%p] [%p]\n",
		pElement, pElement->age, pElement->name, pElement->phone, pElement->pPrev, pElement->pNext);
}


void PrintList(const USERDATA* pHead)
{
	pHead = pHead->pNext;
	while (pHead->pNext != NULL) {
		printf("[%p] %d, %s, %s [%p] [%p]\n",
			pHead, pHead->age, pHead->name, pHead->phone, pHead->pPrev, pHead->pNext);
		pHead = pHead->pNext;
	}
	puts("[End of list]\n");
}

ERROR_CODE Search(USERDATA* pHead, USERDATA* pTail)
{
	printf("[1]SearchByName\t[2]SearchByAgeRange");
	int input;
	if (1 != scanf_s("%d", &input)) {
		return INVALID_INPUT;
	}
	ERROR_CODE result;
	
	if (input == 1) {
		char name[32] = { 0 };
		printf("찾을 요소의 이름을 입력하세요.");
		gets_s(name, sizeof(name));
		USERDATA* pResult = SearchByName(pHead, name);
		if (pResult != NULL) {
			printf("%d, %s, %s\n", pResult->age, pResult->name, pResult->phone);
			result = SUCCESS;
		}
		else
			result = NOT_FOUND;
	}
	else if (input == 2) {
		result = SearchByAgeIndex(pHead, pTail);
	}
	return result;
}

ERROR_CODE New(USERDATA* pTail)
{
	int age = 0;
	char name[32] = { 0 };
	char phone[32] = { 0 };
	printf("나이를 입력하세요. ");
	if (1 != scanf_s("%d", &age)) {
		return INVALID_INPUT;
	}
	printf("이름을 입력하세요.");
	if (1 != scanf_s("%s", name, 32)) {
		return INVALID_INPUT;
	}
	printf("번호를 입력하세요.");
	if (1 != scanf_s("%s", phone, 32)) {
		return INVALID_INPUT;
	}
	AddNewNodeAtTail(pTail, age, name, phone);
	return SUCCESS;
}

ERROR_CODE Remove(USERDATA* pHead)
{
	char name[32] = { 0 };
	printf("삭제할 요소의 이름을 입력하세요.");
	if (1 != scanf_s("%s", name, 32)) {
		return 0;
	}
	ERROR_CODE result = RemoveByName(pHead, name);
	return result;
}

void CheckFuncResult(int result)
{
	switch (result) {
	case SUCCESS:
		printf("성공");
		break;
	case INVALID_INPUT:
		printf("실패 (잘못된 입력값)");
		break;
	case EMPTY:
		printf("실패 (비어있음)");
	case  NOT_FOUND:
		printf("실패 (값을 찾을 수 없음)");
	default:
		;
	}
}

ERROR_CODE Sort(USERDATA* pHead, USERDATA* pTail)
{
	printf("[1]SortByName\t[2]SortByAge");
	int input;
	if (1 != scanf_s("%d", &input)) {
		return INVALID_INPUT;
	}
	ERROR_CODE result;
	if (input == 1)
		result = SortListByName(pHead, pTail);
	else if (input == 2)
		result = SortListByAge(pHead, pTail);
	else
		result = INVALID_INPUT;
	return result;
}

ERROR_CODE SearchByAgeIndex(USERDATA* pHead, USERDATA* pTail)
{
	int min = 0;
	int max = 1;
	size_t cnt = 0;
	printf("[Index search] MIN MAX age: ");
	if (2 != scanf_s("%d%d%*c", &min, &max)) {
		return INVALID_INPUT;
	}
	Sort(pHead, pTail);
	USERDATA** pResult = (USERDATA**)SearchByIndexAgeRange(pHead, &cnt, min, max);
	
	if (pResult == NULL)
		return NOT_FOUND;
	for (int i = 0; i < cnt; ++i) {
		PrintOne(pResult[i]);
	}


	free(pResult);
	return SUCCESS;
}