#pragma once
#include "linkedList.h"
#include "error.h"
typedef enum { EXIT, NEW, SEARCH, PRINT, REMOVE, SORT, } MY_MENU;




MY_MENU PrintMenu(void);
void EventLoopRun(USERDATA* pHead, USERDATA* pTail);
void PrintList(const USERDATA* pHead);
void PrintOne(const USERDATA* pElement);
ERROR_CODE Search(USERDATA* pTail);
ERROR_CODE New(USERDATA* pTail);
ERROR_CODE Remove(USERDATA* pHead);

void CheckFuncResult(ERROR_CODE result);
ERROR_CODE Sort(USERDATA* pHead, USERDATA* pTail);
ERROR_CODE SearchByAgeIndex(USERDATA* pHead);
