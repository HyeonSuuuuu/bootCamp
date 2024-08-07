#pragma once
#include "list.h"

typedef enum {
	EXIT,
	NEW,
	SEARCH,
	EDIT,
	PRINT,
	REMOVE,
} MY_MENU;


MY_MENU PrintMenu(void);
void EventRoopRun(MYNODE_MANAGER* pManager);

int RemoveUser(MYNODE_MANAGER* pManager);
int PrintUser(MYNODE_MANAGER* pManager);
int SearchUser(MYNODE_MANAGER* pManager);
int AddNewUser(MYNODE_MANAGER* pManager);
int EditUser(MYNODE_MANAGER* pManager);
int Exit(MYNODE_MANAGER* pManager);

void ParseUserData(const char* buffer, const char* subStr, char* destination);
int ValidateUserData(MYNODE_MANAGER* pManager, const void* pData);
