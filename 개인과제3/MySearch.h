#pragma once
#include <vector>
#include "MyKey.h"

class UserData;
class MyList;
class MyFile;

class MySearch {
public:
	MySearch(MyList& rList, MyFile& rFile);
	~MySearch();
	MyKey stringToMyKey(const string& key);
	void findNodeAll(const string& strKey, MyKey key);
	void searchFileAll(const string& strKey, MyKey curKey);
	void findSearchListAll(const string& strKey, MyKey key);
	void parse(string& input);
	bool checkValidOffset(UserData& user);
	std::vector<UserData> getSearchList(void) const { return searchList; }

private:
	MyList& list;
	MyFile& file;
	std::vector<UserData> searchList;
};