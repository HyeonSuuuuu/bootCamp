#pragma once
#include <stdbool.h>

typedef struct {
	bool bEmpty;
	char name[32];
	char phone[32];
	char address[100];
} USERDATA;

typedef struct {
	bool bEmpty;
	USERDATA userData;
}USERDATA_WITH_FLAG;

typedef struct {
	bool bNew;
	bool bEmpty;
	void* pDataCache;
	unsigned int sizeOfData;
	unsigned int offset;
	

	struct MYNODE* pNext;
	struct MYNODE* pPrev;

} MYNODE;

typedef struct {
	MYNODE headNode;
	MYNODE tailNode;
	size_t listCount;
	size_t fileDataCount;

	MYNODE** idxListName;
	MYNODE** idxListAddress;
	MYNODE** idxListPhone;
} MYNODE_MANAGER;

typedef enum {
	MY_NAME,
	MY_ADDRESS,
	MY_PHONE,
} MY_KEY;

void* AddNewNodeAtTail(MYNODE_MANAGER* pManger, const void* pData, int sizeData, bool bNew, const size_t* offset);
void* RemoveNode(MYNODE_MANAGER* pManager, const char* pszKey, MY_KEY curKey);
void InitList(MYNODE_MANAGER* pManager);
int IsEmpty(MYNODE_MANAGER* pManager);
void ReleaseList(MYNODE_MANAGER* pManager);
char* GetKey(void* thisPointer, MY_KEY curKey);
int CheckValidKey(MYNODE_MANAGER* pManager, const void* pData);
void** SearchConditional(MYNODE_MANAGER* pManager, char* buffer, int* pCount);

size_t GetEmptyOffset();
size_t CountFileData();
void* SearchList(MYNODE_MANAGER* pManager, char* pszKey, MY_KEY curKey);
int SaveNodeToFile(MYNODE* pNode);
int SaveNewDataToFile(MYNODE_MANAGER* pManager);
int UserDataCopy(USERDATA* pDestination, const USERDATA* pSource);