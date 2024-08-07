#include <stdio.h>
#include <string.h>
#include "dummyUserData.h"
#include "list.h"

void CreateDummyData(const char* filename) {

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    char buffer[1024];

    FILE* fp = fopen("dummy.txt", "w");
    if (fp == NULL) {
        printf("파일을 쓸 수 없습니다.\n");
        return;
    }
    int cnt = 0;
    while (fgets(buffer, sizeof(buffer) / sizeof(char), file)) {
        if (SaveDummyDataToUserData(buffer, fp)) {
            if (++cnt == 10000)
                break;
        }
    }
    fclose(fp);

    fclose(file);
}

int SaveDummyDataToUserData(char* buf, FILE* fp)
{
    char* pszToken = NULL;
    char* pszNextToken = NULL;
    pszToken = strtok_s(buf, "\t", &pszNextToken);
    if (strlen(pszToken) > 30)
        return 0;
    fputs("0,0,", fp);
    fputs(pszToken, fp);
    fputs(",", fp);
    pszToken = strtok_s(NULL, "\t", &pszNextToken);
    fputs(pszToken, fp);
    fputs(",", fp);
    pszToken = strtok_s(NULL, "\t", &pszNextToken);
    fputs(pszToken, fp);
    return 1;
}

int LoadListFromDummyData(MYNODE_MANAGER* pManager)
{
    ReleaseList(pManager);
    FILE* fp = NULL;
    fopen_s(&fp, "dummy.txt", "r");
    if (fp == NULL)
        return 0;

    char buffer[1024];
    int cnt = 0;
    USERDATA user;
    size_t offset = 0;

    while (fgets(buffer, sizeof(buffer) / sizeof(char), fp)) {
        char* pszToken = NULL;
        char* pszNextToken = NULL;
        pszToken = strtok_s(buffer, ",", &pszNextToken);
        if (*pszToken == '0') {
            pszToken = strtok_s(NULL, ",", &pszNextToken);
            pszToken = strtok_s(NULL, ",", &pszNextToken);
            if (strlen(pszToken) >= 30) {
                continue;
            }
            strcpy_s(user.name, sizeof(user.name), pszToken);


            pszToken = strtok_s(NULL, ",", &pszNextToken);
            if (strlen(pszToken) >= 100) {
                continue;
            }
            strcpy_s(user.address, sizeof(user.address), pszToken);
            pszToken = strtok_s(NULL, ",", &pszNextToken);
            if (strlen(pszToken) >= 30) {
                continue;
            }
            strcpy_s(user.phone, sizeof(user.phone), pszToken);
            user.phone[strlen(user.phone)-1] = '\0';
            AddNewNodeAtTail(pManager, &user, sizeof(user), 0, &offset);
            printf("[%d]success %s\n", cnt++, user.name);
            offset++;
        }
    }
    fclose(fp);
    return 1;
}

int SaveListToListFile(MYNODE_MANAGER* pManager)
{
    FILE* fp = NULL;
    fopen_s(&fp, "listData.dat", "rb+");
    if (fp == NULL)
        return 0;

    MYNODE* pTmp = &pManager->headNode;

    size_t cnt = 0;
    USERDATA_WITH_FLAG userWithFlag = { 0 };
    int sizeOfData = sizeof(USERDATA_WITH_FLAG);
    while (pTmp != NULL) {
        if (pTmp->pDataCache != NULL || pTmp->sizeOfData != 0) {
            userWithFlag.userData = *((USERDATA*)pTmp->pDataCache);

            fseek(fp, pTmp->offset * sizeOfData, SEEK_SET);
            fwrite(&userWithFlag, sizeOfData, 1, fp);
            printf("[%d]Success Save\n", cnt++);
        }

        pTmp = pTmp->pNext;
    }
    fclose(fp);
    return 1;
}