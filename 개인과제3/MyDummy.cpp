#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "MyDummy.h"
#include "MyList.h"
#include "MyFile.h"
#include "UserData.h"


MyDummy::MyDummy(const string& fileName)
	: fileName(fileName)
{
}

MyDummy::~MyDummy(void)
{
}

void MyDummy::CreateDummyData(void)
{
    FILE* file = NULL;
    fopen_s(&file, fileName.c_str(), "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    char buffer[1024];
    FILE* fp = NULL;
    fopen_s(&fp, "dummy.txt", "w");
    if (fp == NULL) {
        printf("파일을 쓸 수 없습니다.\n");
        return;
    }
    int cnt = 0;
    while (fgets(buffer, sizeof(buffer) / sizeof(char), file)) {
        SaveDummyDataToUserData(buffer, fp);
    }
    fclose(fp);

    fclose(file);
}

int MyDummy::SaveDummyDataToUserData(char* buf, FILE* fp)
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


int MyDummy::LoadListFromDummyData(MyList& list)
{
    FILE* fp = NULL;
    fopen_s(&fp, tmpFileName, "r");
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
            user.phone[strlen(user.phone) - 1] = '\0';
            list.addNewNode(new UserData(user.name, user.address, user.phone));
            list.getEndNode()->setOffset(offset);
            printf("[%d]success %s\n", cnt++, user.name);
            offset++;
        }
    }
    fclose(fp);
    return 1;
}

int MyDummy::SaveListToListFile(MyList& list)
{
    FILE* fp = NULL;
    fopen_s(&fp, dummyFileData, "rb+");
    if (fp == NULL)
        return 0;

    size_t cnt = 0;
    USERDATA_WITH_FLAG userWithFlag = { 0 };
    int sizeOfData = sizeof(USERDATA_WITH_FLAG);
    for (MyNode& node : list) {
        UserData& user = static_cast<UserData&>(node);
        userWithFlag.userData = MyFile::nodeToUSERDATA(node);
        fseek(fp, node.getOffset() * sizeOfData, SEEK_SET);
        fwrite(&userWithFlag, sizeOfData, 1, fp);
        printf("[%d]Success Save\n", cnt++);
    }
    fclose(fp);
    return 1;
}