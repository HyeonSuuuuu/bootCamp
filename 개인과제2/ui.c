#include <stdio.h>
#include <conio.h>
#include "ui.h"
#include "list.h"



MY_MENU PrintMenu(void)
{
	MY_MENU input;
	system("cls");
	printf("[1]New\t[2]Search\t[3]Edit\t[4]Print\t[5]Remove\t[0]Exit\n");
	if (1 != scanf_s("%d%*c", &input)) {
		printf("입력값이 올바르지 않습니다.\n");
		return 0;
	}
	system("cls");
	return input;
}

void EventLoopRun(MYNODE_MANAGER* pManager)
{
	int (*fp[6])(MYNODE_MANAGER*) = { Exit, AddNewUser, SearchUser, EditUser, PrintUser, RemoveUser, };
	MY_MENU menu;
	while ((menu = PrintMenu()) != 0) {
		if (fp[menu](pManager) == 0) {
			break;
		}
		printf("계속 하려면 아무키나 눌러주세요.\n");
		_getch();
	}
}

int RemoveUser(MYNODE_MANAGER* pManager)
{
	// 삭제를 하는데 일단 캐쉬에 있다면 캐쉬에 있는거 bEmpty를 1로 바꿔주면 되고
	char input[32] = { 0 };
	printf("삭제할 데이터의 전화번호를 입력하세요 ");
	gets_s(input, sizeof(input));
	
	MYNODE* pDelete = RemoveNode(pManager, input, MY_PHONE);
	if (pDelete == NULL) {
		printf("일치하는 데이터가 없습니다.\n");
		return 1;
	}
	// commit을 한다면 update 해주면 된다.
	char ch;
	printf("commit 하겠습니까? (y/n)");
	ch = getchar();
	if (ch == 'y' || ch == 'Y') {
		SaveNodeToFile(pDelete);
		pDelete->bNew = false;
		printf("commit 완료\n");
	}
	return 1;
}

int PrintUser(MYNODE_MANAGER* pManager)
{
	MYNODE* pTmp = &pManager->headNode;
	USERDATA* pUserTmp;
	while (pTmp != NULL) {
		pUserTmp = pTmp->pDataCache;
		printf("------------------------------------------------------------------------\n");
		if (pUserTmp != NULL) {
			if (pTmp->bEmpty)
				printf("<삭제예정>\n");
			printf("offset: %d\n", pTmp->offset);
			printf(">cur:[%p]<\n prev:[%p]\n이름:%s\n번호:%s\n 주소:%s\nnext:[%p]\n\n", pTmp, pTmp->pPrev, pUserTmp->name, pUserTmp->phone, pUserTmp->address, pTmp->pNext);
		}
		else {
			printf(">cur:[%p]<\nprev:[%p]\nnext:[%p]\n\n", pTmp, pTmp->pPrev, pTmp->pNext);
		}
		printf("------------------------------------------------------------------------\n");
		pTmp = pTmp->pNext;
	}
	return 1;
}



int AddNewUser(MYNODE_MANAGER* pManager)
{
	USERDATA user = { 0 };

	printf("name: ");
	gets_s(user.name, sizeof(user.name));
	printf("address: ");
	gets_s(user.address, sizeof(user.address));
	printf("phone: ");
	gets_s(user.phone, sizeof(user.phone));

	if (!ValidateUserData(pManager, &user)) {
		return 1;
	}
	MYNODE* pResult = AddNewNodeAtTail(pManager, &user, sizeof(user), true, NULL);
	char ch;
	printf("commit 하겠습니까? (y/n)");
	ch = getchar();
	if (ch == 'y' || ch == 'Y') {
		SaveNodeToFile(pResult);
		pResult->bNew = false;
		printf("commit 완료\n");
	}
	return 1;
}

int SearchUser(MYNODE_MANAGER* pManager)
{
	char buffer[150];
	
	if (1 != scanf_s("%[^\n]s",buffer, sizeof(buffer))) {
		return 1;
	}
	int cnt = 0;
	USERDATA** pDataList = NULL;
	USERDATA* pData = NULL;
	pDataList = (USERDATA**)SearchConditional(pManager, buffer, &cnt);
	if (pDataList == NULL) {
		printf("조건에 맞는 데이터를 찾을 수 없습니다.\n");
		return 1;
	}
	for (int i = 0; i < cnt; ++i) {
		pData = pDataList[i];
		printf("이름:%s\n주소:%s\n번호:%s\n", pData->name, pData->address, pData->phone);
	}
	free(pDataList);
	return 1;
}

int Exit(MYNODE_MANAGER* pManager)
{
	return 0;
}

int EditUser(MYNODE_MANAGER* pManager)
{
	char* buffer[100];
	printf("input: ");
	if (1 != scanf_s("%s%*c", buffer, sizeof(buffer))) {
		return 1;
	}


	MYNODE* pNode = NULL;
	USERDATA* pUserData = NULL;
	pNode = (MYNODE*)SearchList(pManager, buffer, MY_NAME);
	if (pNode == NULL) {
		printf("Not Found\n");
		return 1;
	}
	pUserData = pNode->pDataCache;
	
	printf("이름:%s\n주소:%s\n번호:%s\n", pUserData->name, pUserData->address, pUserData->phone);
	if (pNode->bEmpty) {
		printf("<삭제 예정된 데이터입니다.>\n");
		return 1;
	}
	printf("수정하겠습니까?(y/n) ");
	char ch;
	ch = getchar();
	getchar();
	USERDATA editUserData;

	if (ch == 'y' || ch == 'Y') {
		printf("name: ");
		gets_s(editUserData.name, sizeof(editUserData.name));
		printf("address: ");
		gets_s(editUserData.address, sizeof(editUserData.address));
		printf("phone: ");
		gets_s(editUserData.phone, sizeof(editUserData.phone));
		
		if (!ValidateUserData(pManager, &editUserData) && (strlen(editUserData.phone, pUserData->phone) != 0)) {
			// 이름도 같고 전화번호도 같은 경우 >> 예외처리
			return 1;
		}

		if (UserDataCopy(pUserData, &editUserData) == 0) {
			printf("복사실패\n");
			return 1;
		}
		pNode->bNew = true;

		char ch;
		printf("commit 하겠습니까? (y/n)");
		ch = getchar();
		if (ch == 'y' || ch == 'Y') {
			SaveNodeToFile(pNode);
			pNode->bNew = false;
			printf("commit 완료\n");
		}
	}
	return 1;
}



int ValidateUserData(MYNODE_MANAGER* pManager, const void* pData)
{
	USERDATA* pUserData = (USERDATA*)pData;
	if (pUserData->name[0] == '\0' || pUserData->address[0] == '\0' || pUserData->phone[0] == '\0') {
		printf("공백의 데이터를 추가할 수 없습니다.\n");
		return 0;
	}
	if (!CheckValidKey(pManager, pData)) {
		printf("중복된 값이 있습니다.(key: phone)\n");
		return 0;
	}
	return 1;
}