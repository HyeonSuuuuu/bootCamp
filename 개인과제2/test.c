#include<stdio.h>
#include "test.h"
#include "list.h"



void AddNodeTest(MYNODE_MANAGER* pManager)
{
	USERDATA user[2] = { {"홍길동", "010-1234-5678", "주소1"}, {"김길동", "010-2345-3456", "주소2"} };
	AddNewNodeAtTail(pManager, &user[0], sizeof(user[0]), 0, 0);
	AddNewNodeAtTail(pManager, &user[1], sizeof(user[1]), 0, 0);

	MYNODE* pTmp = &pManager->headNode;
	USERDATA* pUserTmp;
	while (pTmp != NULL) {
		pUserTmp = pTmp->pDataCache;
		if(pUserTmp != NULL)
			printf(">cur:[%p]<\nprev:[%p]\n이름:%s\n번호:%s\n 주소:%s\nnext:[%p]\n\n", pTmp, pTmp->pPrev, pUserTmp->name, pUserTmp->phone, pUserTmp->address, pTmp->pNext);
		else {
			printf(">cur:[%p]<\nprev:[%p]\nnext:[%p]\n\n", pTmp, pTmp->pPrev, pTmp->pNext);
		}
		pTmp = pTmp->pNext;
	} 
}