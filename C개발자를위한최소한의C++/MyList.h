#pragma once
#include <string>

using std::string;


class MyList {
public:
	int addNewNode(string pszName, string pszPhone);

	void releaseList();
private:
	UserData* pHead = nullptr;
};