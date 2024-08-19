#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "dummyUserData.h"
#include "list.h"
#include "test.h"


int main() {

    MYNODE_MANAGER manager = { 0 };
    InitList(&manager);
    
    EventLoopRun(&manager);
    SaveNewDataToFile(&manager);
    ReleaseList(&manager);
    return 0;
}


 //             dummy data ����

//int main()
//{
//    const char* filename = "������_�����ߵ����� �ּҷ� �� ����ó.txt";
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