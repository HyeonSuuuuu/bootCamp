#include <iostream>
#include "StatisticsUI.h"
#include "MyList.h"
#include "Myfile.h"
#include "UserData.h"


using namespace std;


StatisticsUI::StatisticsUI(MyList& rList, MyFile& rFile)
	: list(rList), file(rFile)
{

	list.addObserver(this);
	file.addObserver(this);
}



void StatisticsUI::display(void)
{

    cout << "Memory List: " << list.getListCounter();
    cout << "\tFile List: " << file.countFileData() << endl;
}




void StatisticsUI::notify(void)
{
    display();
}