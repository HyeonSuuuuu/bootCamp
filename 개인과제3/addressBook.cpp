#include "UserInterface.h"
#include "StatisticsUI.h"
#include "Mylist.h"
#include "UserData.h"
#include "MyFile.h"
#include "MyDummy.h"
#include "Observer.h"

using namespace std;


int main(void)
{
	UserInterface UI(MyList::get(), MyFile::get("listData.dat", MyList::get()));
	StatisticsUI statUI(MyList::get(), MyFile::get("listData.dat", MyList::get()));
	UI.run();
	MyFile::get("listData.dat", MyList::get()).saveNewDataToFile();
}




//						dummy data 생성
//int main(void)
//{
//	MyList DB(new UserData("Dummy", "Head", "Data"), new UserData("Dummy", "Tail", "Data"));
//	MyFile file("listData.dat", DB);
//	UserInterface UI(DB, file);
//	MyDummy dummy("교육부_유초중등교육기관 주소록 및 연락처.txt");
//	dummy.CreateDummyData();
//	dummy.LoadListFromDummyData(DB);
//	dummy.SaveListToListFile(DB);
//
//	UI.run();
//}