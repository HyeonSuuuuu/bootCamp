#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "ui.h"

const char* filename = "listData.dat";


void InitList(MYNODE_MANAGER* pManager)
{
	ReleaseList(pManager);
	MYNODE* pHeadNode = &pManager->headNode;
	MYNODE* pTailNode = &pManager->tailNode;

	pHeadNode->pNext = pTailNode;
	pTailNode->pPrev = pHeadNode;
	pManager->listCount = 0;
	pManager->fileDataCount = CountFileData();
}
int IsEmpty(MYNODE_MANAGER* pManager)
{
	MYNODE* pHeadNode = &pManager->headNode;
	MYNODE* pTailNode = &pManager->tailNode;
	if (pHeadNode->pNext == pTailNode || pHeadNode->pNext == NULL) {
		return 1;
	}

	return 0;
}

void ReleaseList(MYNODE_MANAGER* pManager)
{
	if (IsEmpty(pManager))
		return;
	MYNODE* pHeadNode = &pManager->headNode;
	MYNODE* pTailNode = &pManager->tailNode;


	MYNODE* pTmp = pHeadNode->pNext;
	MYNODE* pDelete;
	while (pTmp != pTailNode) {
		pDelete = pTmp;
		pTmp = pTmp->pNext;

		if (pDelete->pDataCache != NULL)
			free(pDelete->pDataCache);
		free(pDelete);
	}

	pHeadNode->pNext = pTailNode;
	pTailNode->pPrev = pHeadNode;
	pManager->listCount = 0;
}

char* GetKey(void* thisPointer, MY_KEY curKey)
{
	USERDATA* pUser = (USERDATA*)thisPointer;
	switch (curKey) {
	case MY_NAME:
		return pUser->name;
		break;
	case MY_ADDRESS:
		return pUser->address;
		break;
	case MY_PHONE:
		return pUser->phone;
		break;
	default:
		return NULL;
	}
}

int CheckValidKey(MYNODE_MANAGER* pManager, const void* pData)
{
	if (NULL != SearchList(pManager, ((USERDATA*)pData)->phone, MY_PHONE)) {
		return 0;
	}
	return 1;
}

void* RemoveNode(MYNODE_MANAGER* pManager, const char* pszKey, MY_KEY curKey)
{
	MYNODE* pHeadNode = &pManager->headNode;
	MYNODE* pTailNode = &pManager->tailNode;

	MYNODE* pTmp = pHeadNode->pNext;
	
	pTmp = SearchList(pManager, pszKey, curKey);
	if (pTmp != NULL) {
		pTmp->bNew = true;
		pTmp->bEmpty = true;
	}
	return pTmp;
}

size_t GetEmptyOffset()
{
	FILE* fp = NULL;
	fopen_s(&fp, filename, "rb");
	if (fp == NULL)
		return NULL;
	USERDATA_WITH_FLAG userWithFlag = { 0 };
	size_t offset = 0;
	while (fread(&userWithFlag, sizeof(USERDATA_WITH_FLAG), 1, fp) > 0) {
		if (userWithFlag.bEmpty) {
			fclose(fp);
			return offset;
		}
		fseek(fp, ++offset * sizeof(USERDATA_WITH_FLAG), SEEK_SET);
	}
	fclose(fp);
	return offset+1;
}

void* AddNewNodeAtTail(MYNODE_MANAGER* pManager, const void* pData, int sizeData, bool bNew, const size_t* offset)
{
	MYNODE* pNewNode = calloc(1, sizeof(MYNODE));

	if (pData != NULL && sizeData > 0) {
		void* pNewData = malloc(sizeData);
		memcpy(pNewData, pData, sizeData);
		pNewNode->pDataCache = pNewData;
		pNewNode->sizeOfData = sizeData;
	}

	pNewNode->bEmpty = false;
	pNewNode->bNew = bNew;
	if (offset == NULL) {
		pNewNode->offset = GetEmptyOffset();
	}
	else {
		pNewNode->offset = *offset;
	}
	MYNODE* pTailNode = &pManager->tailNode;

	MYNODE* pPrevNode = pTailNode->pPrev;
	pPrevNode->pNext = pNewNode;
	pNewNode->pPrev = pPrevNode;
	pNewNode->pNext = pTailNode;
	pTailNode->pPrev = pNewNode;
	++pManager->listCount;
	return pNewNode;
}

size_t CountFileData()
{
	FILE* fp = NULL;
	fopen_s(&fp, filename, "rb");
	if (fp == NULL)
		return NULL;

	USERDATA_WITH_FLAG userWithFlag = { 0 };
	size_t offset = 0;
	while (fread(&userWithFlag, sizeof(USERDATA_WITH_FLAG), 1, fp) > 0) {
		fseek(fp, ++offset * sizeof(USERDATA_WITH_FLAG), SEEK_SET);
	}
	fclose(fp);
	return offset;
}

void* SearchList(MYNODE_MANAGER* pManager, char* pszKey, MY_KEY myKey) // 나중에 구현
{
	MYNODE* pHeadNode = &pManager->headNode;
	MYNODE* pTailNode = &pManager->tailNode;

	//먼저 캐쉬에서 값을 찾음
	MYNODE* pTmp = pHeadNode->pNext;
	while (pTmp != pTailNode) {
		if (strcmp(GetKey(pTmp->pDataCache, myKey), pszKey) == 0) {
			return pTmp;
		}
		pTmp = pTmp->pNext;
	}
	
	FILE* fp = NULL;
	fopen_s(&fp, filename, "rb");
	if (fp == NULL) 
		return NULL;
	USERDATA_WITH_FLAG userWithFlag = { 0 };
	size_t offset = 0;
	MYNODE* pTarget;
	while (fread(&userWithFlag, sizeof(USERDATA_WITH_FLAG), 1, fp) > 0) {
		if (!userWithFlag.bEmpty) {
			if (strcmp(GetKey(&userWithFlag.userData, myKey), pszKey) == 0) {
				AddNewNodeAtTail(pManager, &userWithFlag.userData, sizeof(USERDATA), 0, &offset);
				pTarget = pManager->tailNode.pPrev;
				fclose(fp);
				return pTarget;
			}
		}
		fseek(fp, ++offset * sizeof(USERDATA_WITH_FLAG), SEEK_SET);
	}
	fclose(fp);
	return NULL;
  }

int SaveNewDataToFile(MYNODE_MANAGER* pManager)
{
	MYNODE* pHeadNode = &pManager->headNode;
	MYNODE* pTailNode = &pManager->tailNode;

	MYNODE* pTmp = pHeadNode->pNext;
	USERDATA_WITH_FLAG pDataWithFlag;
	while (pTmp != NULL && pTmp != pTailNode)
	{
		if (pTmp->bNew == true) {
			SaveNodeToFile(pTmp);
		}

		pTmp = pTmp->pNext;
	}
	return 1;
}

void ParseUserData(const char* buffer, const char* subStr, char* destination, int destSize)
{
	char* start = NULL;
	char* end = NULL;

	start = strstr(buffer, subStr);
	if (start != NULL) {
		start += strlen(subStr);
		end = strchr(start, '\'');
		if (end != NULL && end - start < 32) {
			strncpy_s(destination, destSize, start, end - start);
			destination[end - start] = '\0';
		}
	}
}

void** SearchConditional(MYNODE_MANAGER* pManager, char* buffer, int* pCount)
{
	USERDATA searchUser = { 0 };
	char* start = NULL;
	char* end = NULL;

	ParseUserData(buffer, "이름='", searchUser.name, 32);
	ParseUserData(buffer, "전화번호='", searchUser.phone, 32);
	ParseUserData(buffer, "주소='", searchUser.address, 100);

	MYNODE* pHeadNode = &pManager->headNode;
	MYNODE* pTailNode = &pManager->tailNode;
	
	MYNODE* pTmp = pHeadNode->pNext;
	MYNODE* pTarget = NULL;

	if (strstr(buffer, "and") == NULL) {
		while (pTmp != pTailNode) {
			if (pTmp->bEmpty == false && pTmp->bNew == true) {
				if ((searchUser.name[0] == '\0' || strcmp(GetKey(&(pTmp->pDataCache), MY_NAME), searchUser.name) == 0) &&
					(searchUser.phone[0] == '\0' || strcmp(GetKey(&(pTmp->pDataCache), MY_PHONE), searchUser.phone) == 0) &&
					(searchUser.address[0] == '\0' || strcmp(GetKey(&(pTmp->pDataCache), MY_ADDRESS), searchUser.address) == 0))
				{
					AddNewNodeAtTail(pManager, pTmp->pDataCache, sizeof(USERDATA), 0, &pTmp->offset);
					if (pTarget == NULL) {
						pTarget = pTailNode->pPrev;
					}
					(*pCount)++;
				}
			}
			pTmp = pTmp->pNext;
		}
		FILE* fp = NULL;
		fopen_s(&fp, filename, "rb");
		if (fp == NULL)
			return NULL;
		USERDATA_WITH_FLAG userWithFlag = { 0 };
		size_t offset = 0;
		while (fread(&userWithFlag, sizeof(USERDATA_WITH_FLAG), 1, fp) > 0) {
			if (!userWithFlag.bEmpty) {
				if ((searchUser.name[0] == '\0' || strcmp(userWithFlag.userData.name, searchUser.name) == 0) &&
					(searchUser.phone[0] == '\0' || strcmp(userWithFlag.userData.phone, searchUser.phone) == 0) &&
					(searchUser.address[0] == '\0' || strcmp(userWithFlag.userData.address, searchUser.address) == 0))
				{
					AddNewNodeAtTail(pManager, &userWithFlag.userData, sizeof(USERDATA), 0, &offset);
					if (pTarget == NULL) {
						pTarget = pTailNode->pPrev;
					}
					(*pCount)++;
				}
			}
			fseek(fp, ++offset * sizeof(USERDATA_WITH_FLAG), SEEK_SET);
		}
		fclose(fp);
	}
	else if (strstr(buffer, "or") == NULL) {
		while (pTmp != pTailNode) {
			if (pTmp->bEmpty == false && pTmp->bNew == true) {
				if ((strcmp(GetKey(&(pTmp->pDataCache), MY_NAME), searchUser.name) == 0) ||
					(strcmp(GetKey(&(pTmp->pDataCache), MY_PHONE), searchUser.phone) == 0) ||
					(strcmp(GetKey(&(pTmp->pDataCache), MY_ADDRESS), searchUser.address) == 0))
				{
					AddNewNodeAtTail(pManager, pTmp->pDataCache, sizeof(USERDATA), 0, &pTmp->offset);
					if (pTarget == NULL) {
						pTarget = pTailNode->pPrev;
					}
					(*pCount)++;
				}
			}
			pTmp = pTmp->pNext;
		}
		FILE* fp = NULL;
		fopen_s(&fp, filename, "rb");
		if (fp == NULL)
			return NULL;
		USERDATA_WITH_FLAG userWithFlag = { 0 };
		size_t offset = 0;
		while (fread(&userWithFlag, sizeof(USERDATA_WITH_FLAG), 1, fp) > 0) {
			if (!userWithFlag.bEmpty) {
				if ((strcmp(userWithFlag.userData.name, searchUser.name) == 0) ||
					(strcmp(userWithFlag.userData.phone, searchUser.phone) == 0) ||
					(strcmp(userWithFlag.userData.address, searchUser.address) == 0))
				{
					AddNewNodeAtTail(pManager, &userWithFlag.userData, sizeof(USERDATA), 0, &offset);
					if (pTarget == NULL) {
						pTarget = pTailNode->pPrev;
					}
					(*pCount)++;
				}
			}
			fseek(fp, ++offset * sizeof(USERDATA_WITH_FLAG), SEEK_SET);
		}
		fclose(fp);
	}

	else {
		if (searchUser.name[0] != '\0') {
			pTarget = SearchList(pManager, searchUser.name, MY_NAME);
			if (pTarget == NULL)
				return NULL;
			(*pCount)++;
		}
		if (searchUser.address[0] == '\0') {
			pTarget = SearchList(pManager, searchUser.address, MY_ADDRESS);
			if (pTarget == NULL)
				return NULL;
			(*pCount)++;
		}
		if (searchUser.phone[0] == '\0') {
			pTarget = SearchList(pManager, searchUser.phone, MY_PHONE);
			if (pTarget == NULL)
				return NULL;
			(*pCount)++;
		}
	}

	void** pNodePtrList = malloc(sizeof(void*) * *pCount);
	for (int i = 0; i < *pCount; ++i) {
		pNodePtrList[i] = pTarget->pDataCache;
		pTarget = pTarget->pNext;
	}
	return pNodePtrList;

}

int SaveNodeToFile(MYNODE* pNode) 
{
	if (pNode->pDataCache == NULL || pNode->sizeOfData == 0)
		return 0;

	FILE* fp = NULL;
	fopen_s(&fp, filename, "rb+");
	if (fp == NULL)
		return 0;
	
	fseek(fp, pNode->offset * sizeof(USERDATA_WITH_FLAG), SEEK_SET);
	USERDATA_WITH_FLAG userDataWithFlag;
	userDataWithFlag.bEmpty = pNode->bEmpty;
	if (1 != UserDataCopy(&userDataWithFlag.userData, pNode->pDataCache)) {
		return 0;
	}
	if (fwrite(&userDataWithFlag, sizeof(USERDATA_WITH_FLAG), 1, fp) > 0) {
		fclose(fp);
		return 1;
	}
	return 0;
}


int UserDataCopy(USERDATA* pDestination, const USERDATA* pSource)
{
	if (0 != strcpy_s(pDestination->name, strlen(pSource->name) + 1, pSource->name))
		return 0;
	if (0 != strcpy_s(pDestination->address, strlen(pSource->address) + 1, pSource->address))
		return 0;
	if (0 != strcpy_s(pDestination->phone, strlen(pSource->phone) + 1, pSource->phone))
		return 0;
	return 1;
}
