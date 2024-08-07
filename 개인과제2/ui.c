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
		printf("�Է°��� �ùٸ��� �ʽ��ϴ�.\n");
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
		printf("��� �Ϸ��� �ƹ�Ű�� �����ּ���.\n");
		_getch();
	}
}

int RemoveUser(MYNODE_MANAGER* pManager)
{
	// ������ �ϴµ� �ϴ� ĳ���� �ִٸ� ĳ���� �ִ°� bEmpty�� 1�� �ٲ��ָ� �ǰ�
	char input[32] = { 0 };
	printf("������ �������� ��ȭ��ȣ�� �Է��ϼ��� ");
	gets_s(input, sizeof(input));
	
	MYNODE* pDelete = RemoveNode(pManager, input, MY_PHONE);
	if (pDelete == NULL) {
		printf("��ġ�ϴ� �����Ͱ� �����ϴ�.\n");
		return 1;
	}
	// commit�� �Ѵٸ� update ���ָ� �ȴ�.
	char ch;
	printf("commit �ϰڽ��ϱ�? (y/n)");
	ch = getchar();
	if (ch == 'y' || ch == 'Y') {
		SaveNodeToFile(pDelete);
		pDelete->bNew = false;
		printf("commit �Ϸ�\n");
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
				printf("<��������>\n");
			printf("offset: %d\n", pTmp->offset);
			printf(">cur:[%p]<\n prev:[%p]\n�̸�:%s\n��ȣ:%s\n �ּ�:%s\nnext:[%p]\n\n", pTmp, pTmp->pPrev, pUserTmp->name, pUserTmp->phone, pUserTmp->address, pTmp->pNext);
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
	printf("commit �ϰڽ��ϱ�? (y/n)");
	ch = getchar();
	if (ch == 'y' || ch == 'Y') {
		SaveNodeToFile(pResult);
		pResult->bNew = false;
		printf("commit �Ϸ�\n");
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
		printf("���ǿ� �´� �����͸� ã�� �� �����ϴ�.\n");
		return 1;
	}
	for (int i = 0; i < cnt; ++i) {
		pData = pDataList[i];
		printf("�̸�:%s\n�ּ�:%s\n��ȣ:%s\n", pData->name, pData->address, pData->phone);
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
	
	printf("�̸�:%s\n�ּ�:%s\n��ȣ:%s\n", pUserData->name, pUserData->address, pUserData->phone);
	if (pNode->bEmpty) {
		printf("<���� ������ �������Դϴ�.>\n");
		return 1;
	}
	printf("�����ϰڽ��ϱ�?(y/n) ");
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
			// �̸��� ���� ��ȭ��ȣ�� ���� ��� >> ����ó��
			return 1;
		}

		if (UserDataCopy(pUserData, &editUserData) == 0) {
			printf("�������\n");
			return 1;
		}
		pNode->bNew = true;

		char ch;
		printf("commit �ϰڽ��ϱ�? (y/n)");
		ch = getchar();
		if (ch == 'y' || ch == 'Y') {
			SaveNodeToFile(pNode);
			pNode->bNew = false;
			printf("commit �Ϸ�\n");
		}
	}
	return 1;
}



int ValidateUserData(MYNODE_MANAGER* pManager, const void* pData)
{
	USERDATA* pUserData = (USERDATA*)pData;
	if (pUserData->name[0] == '\0' || pUserData->address[0] == '\0' || pUserData->phone[0] == '\0') {
		printf("������ �����͸� �߰��� �� �����ϴ�.\n");
		return 0;
	}
	if (!CheckValidKey(pManager, pData)) {
		printf("�ߺ��� ���� �ֽ��ϴ�.(key: phone)\n");
		return 0;
	}
	return 1;
}