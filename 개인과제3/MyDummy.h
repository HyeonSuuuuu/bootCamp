#pragma once
#include <string>

using std::string;

class MyList;

class MyDummy {
public:
	MyDummy(const string& fileName);
	~MyDummy(void);

	void CreateDummyData(void);
	int SaveDummyDataToUserData(char* buf, FILE* fp);
	int LoadListFromDummyData(MyList& list);
	int SaveListToListFile(MyList& list);
private:
	string fileName;
	const char* tmpFileName = "dummy.txt";
	const char* dummyFileData = "listData.dat";
};