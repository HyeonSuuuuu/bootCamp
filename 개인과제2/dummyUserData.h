#pragma once
#include "list.h"

void CreateDummyData(const char* filename);
int SaveDummyDataToUserData(char* buf, FILE* fp);
int LoadListFromDummyData(MYNODE_MANAGER* pManager);
int SaveNodeToListFile(MYNODE_MANAGER* pManager);
