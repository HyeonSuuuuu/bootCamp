#include <iostream>
#include "MyList.h"
#include "UserData.h"

using namespace std;



int addNewNode(string pszName, string pszPhone)
{
	UserData* pNewUser = NULL;

	// ���� �̸��� �̹� �����ϴ��� Ȯ���Ѵ�.
	if (findNode(pszName) != NULL)
		return 0;

	// �޸𸮸� Ȯ���Ѵ�.
	pNewUser = (USERDATA*)malloc(sizeof(USERDATA));
	memset(pNewUser, 0, sizeof(USERDATA));

	// �޸𸮿� ���� �����Ѵ�.
	sprintf_s(pNewUser->szName, sizeof(pNewUser->szName), "%s", pszName);
	sprintf_s(pNewUser->szPhone, sizeof(pNewUser->szPhone), "%s", pszPhone);
	pNewUser->pNext = NULL;

	// ���� ��� �ٷ� �ڿ� ���δ�. ���� ���� �ֱٿ�
	// �߰��� �����Ͱ� ���� ���ʿ� �´�. 
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
