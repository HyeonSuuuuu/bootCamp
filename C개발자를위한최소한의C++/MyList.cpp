#include <iostream>
#include "MyList.h"
#include "UserData.h"

using namespace std;



int addNewNode(string pszName, string pszPhone)
{
	UserData* pNewUser = NULL;

	// 같은 이름이 이미 존재하는지 확인한다.
	if (findNode(pszName) != NULL)
		return 0;

	// 메모리를 확보한다.
	pNewUser = (USERDATA*)malloc(sizeof(USERDATA));
	memset(pNewUser, 0, sizeof(USERDATA));

	// 메모리에 값을 저장한다.
	sprintf_s(pNewUser->szName, sizeof(pNewUser->szName), "%s", pszName);
	sprintf_s(pNewUser->szPhone, sizeof(pNewUser->szPhone), "%s", pszPhone);
	pNewUser->pNext = NULL;

	// 더미 노드 바로 뒤에 붙인다. 따라서 가장 최근에
	// 추가한 데이터가 가장 앞쪽에 온다. 
	pNewUser->pNext = g_Head.pNext;
	g_Head.pNext = pNewUser;

	return 1;
}


void MyList::releaseList()
{
	USERDATA* pTmp = g_Head.pNext;
	USERDATA* pDelete = NULL;

	while (pTmp != NULL) {
		pDelete = pTmp;
		pTmp = pTmp->pNext;

		free(pDelete);
	}

	memset(&g_Head, 0, sizeof(USERDATA));
}
