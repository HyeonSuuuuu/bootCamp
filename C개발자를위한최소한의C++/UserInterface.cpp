#include <iostream>
#include "UserInterface.h"
#include "MyList.h"
using namespace std;


int UserInterface::printUI()
{
	int nInput = 0;

	system("cls");
	cout <<"[1] Add\t [2] Search\t [3] Print all\t [4] Remove\t [0] Exit\n:";
	cin >> nInput;

	return nInput;
}

void UserInterface::run()
{
	int nMenu = 0;

	// 메인 이벤트 반복문
	while ((nMenu = printUI()) != 0) {
		switch (nMenu) {
		case 1:		  // Add
			addUser();
			break;

		case 2:		  // Search
			searchUser();
			break;

		case 3:		 // Print all
			printAll();
			break;

		case 4:		  // Remove
			removeUser();
			break;
		}
	}
	releaseList();
}