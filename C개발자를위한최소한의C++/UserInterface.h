#pragma once


class UserInterface {


public:
	UserInterface(MyList myList) {
		this->myList = myList;
	}

	int printUI();
	void run();
private:
	MyList& myList;
};