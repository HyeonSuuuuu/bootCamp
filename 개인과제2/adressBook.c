#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "dummyUserData.h"
#include "list.h"
#include "test.h"
#include <string.h>
int main() {
    MYNODE_MANAGER manager = { 0 };
    InitList(&manager);
    
    EventLoopRun(&manager);
    SaveNewDataToFile(&manager);
    ReleaseList(&manager);
    return 0;
}


 //             dummy data 10000개 생성

//int main()
//{
//    const char* filename = "교육부_유초중등교육기관 주소록 및 연락처.txt";
//    CreateDummyData(filename);
//
//    MYNODE_MANAGER manager = { 0 };
//    InitList(&manager);
//    LoadListFromDummyData(&manager);
//    SaveListToListFile(&manager);
//    EventLoopRun(&manager);
//    ReleaseList(&manager);
//    return 0;
//}