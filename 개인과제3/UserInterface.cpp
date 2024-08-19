#include <iostream>
#include <conio.h>
#include <vector>
#include "UserInterface.h"
#include "MyList.h"
#include "UserData.h"
#include "MyKey.h"
#include "MyFile.h"
#include "MySearch.h"
using namespace std;


UserInterface::UserInterface(MyList& rList, MyFile& rFile)
	: list(rList), file(rFile)
{
	list.addObserver(this);
	file.addObserver(this);
}

UserInterface::~UserInterface(void)
{
}

void UserInterface::add(void)
{
	string strName, strAddress, strPhone;

	cout << "Input name : ";
	cin >> strName;
	cout << "Input address : ";
	cin >> strAddress;
	cout << "Input phone number : ";
	cin >> strPhone;
	
	if (!file.checkValidValue(strPhone, MyKey::Phone)) {
		throw 2;
	}

	MyNode* node = list.addNewNode(new UserData(strName, strAddress, strPhone));

	if (node == nullptr) {
		throw 2;
	}
	node->setOffset(file.getEmptyOffset());
	cout << "commit? (y/n) ";
	char ch;
	cin >> ch;

	if (ch == 'y' || ch == 'Y') {
		file.saveNodeToFile(*node);
		cout << "Success commit" << endl;
	}
}

void UserInterface::edit(void)
{
	string strKey;
	cout << "Input phone: ";
	cin >> strKey;

	UserData* pNode = static_cast<UserData*>(list.findNode(strKey, MyKey::Phone));
	if (pNode == nullptr)
		pNode = static_cast<UserData*>(file.searchFile(strKey, MyKey::Phone));
	if (pNode != nullptr)
		pNode->printNode();
	else
		throw 1;
	
	cout << "Edit? (y/n) ";
	char ch;
	cin >> ch;

	if (ch == 'y' || ch == 'Y') {
		string strName, strAddress, strPhone;

		cout << "Input name : ";
		cin >> strName;
		cout << "Input address : ";
		cin >> strAddress;
		cout << "Input phone number : ";
		cin >> strPhone;
		if (strPhone != pNode->getKey()) {
			if (!file.checkValidValue(strPhone, MyKey::Phone)) {
				throw 2;
			}

			if (list.findNode(pNode->getKey(), MyKey::Phone) != nullptr) {
				throw 2;
			}
		}
		
		pNode->setName(strName);
		pNode->setAddress(strAddress);
		pNode->setPhone(strPhone);

		cout << "commit? (y/n) ";
		char ch;
		cin >> ch;

		if (ch == 'y' || ch == 'Y') {
			file.saveNodeToFile(*pNode);
			cout << "Success commit" << endl;
		}
	}

}

void UserInterface::search(void)
{
	string input;
	cout << "Input search condition: ";
	cin.ignore();
	getline(cin, input, '\n');

	MySearch search(list, file);
	search.parse(input);
	if (search.getSearchList().empty()) {
		throw 1;
	}
	for (UserData& user : search.getSearchList()) {
		user.printNode();
	}
}

void UserInterface::remove(void)
{
	string strPhone;
	cout << "Input phone: ";
	cin >> strPhone;

	MyNode* node = list.findNode(strPhone, MyKey::Phone);
	if (node == nullptr) {
		node = file.searchFile(strPhone, MyKey::Phone);
	}
	
	if (node == nullptr)
		throw 1;
	node->setDelete(true);
	node->setNew(true);
	cout << "commit? (y/n)";
	char ch;
	cin >> ch;

	if (ch == 'y' || ch == 'Y') {
		file.saveNodeToFile(*node);
		if (list.removeNode(strPhone))
			cout << "Success commit" << endl;
		else
			throw 1;
	}

	
}

void UserInterface::printAll(void)
{
	size_t cnt = 0;

	cout << "-----------------------------------*----Memory List----*-----------------------------------" << endl;
	for (MyNode& node : list) {
		node.printNode();
		if (!(++cnt % maxOutput)) {
			cout << "Press any key to continue...";
			_getch();
		}
	}
	cout << "-------------------------------------------------------------------------------------------" << endl;

	cout << "Print fileData? (y/n) ";
	char ch;
	cin >> ch;
	if (ch == 'y' || ch == 'Y') {
		cout << "-----------------------------------*----File Data----*-----------------------------------" << endl;
		file.printAll(maxOutput);
		cout << "-------------------------------------------------------------------------------------------" << endl;
	}
	
}


int UserInterface::printUI()
{
	int nInput = 0;

	system("cls");
	cout << "[1] Add\t [2] Search\t [3] Print all\t [4] Remove [5] Edit\t [6] Statistics [0] Exit" << endl;
	cin >> nInput;

	return nInput;
}

void UserInterface::save()
{
}


int UserInterface::run(void)
{
	int nMenu = 0;
	
	while ((nMenu = printUI()) != 0) {
		try {
			switch (nMenu) {
			case 1:
				add();
				break;
			case 2:
				search();
				break;
			case 3:
				printAll();
				break;
			case 4:
				remove();
				break;
			case 5:
				edit();
				break;
			case 6:
				file.notifyAll();
			}
		}
		catch(int nExp) {
			switch (nExp) {
			case 1:
				cout << "ERROR: 데이터를 찾을 수 없습니다." << endl;
				break;
			case 2:
				cout << "ERROR: 중복된 값이 이미 존재합니다." << endl;
				break;

			case 3:
				cout << "ERROR: Add하던 도중 에러가 발생하였습니다." << endl;
				break;
			case 4:
				cout << "입력값이 올바르지 않습니다." << endl;
				break;
			}
		}
		cout << "계속하려면 아무 키나 누르세요.";
		_getch();	}
	return nMenu;
}

void UserInterface::notify(void)
{
	;
}