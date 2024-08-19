#pragma once
#include <string>
#include <fstream>
#include "MyKey.h"
#include "MyNode.h"
#include "Observer.h"

using std::string;

class MyList;

struct USERDATA {
	char name[32];
	char phone[32];
	char address[100];

	const char* getSearchKey(const MyKey key);
};

struct USERDATA_WITH_FLAG {
	bool bEmpty;
	USERDATA userData;
};

class MyFile : public Observable {
public:
	static MyFile& get(const string& fileName, MyList& list)
	{
		static MyFile* myFile = new MyFile(fileName, list);
		return *myFile;
	}

	MyFile(const MyFile&) = delete;
	MyFile(MyFile&&) = delete;
	MyFile& operator=(const MyFile&) = delete;
	MyFile& operator=(MyFile&&) = delete;

	const string& getFileName() const { return fileName; }
	size_t getEmptyOffset();
	size_t countFileData();
	void printAll(size_t maxOutput) const;
	MyNode* searchFile(const string& strKey, MyKey curKey);
	int saveNodeToFile(MyNode& node);
	int saveNewDataToFile(void);
	int userDataCopy(USERDATA* pDestination, const USERDATA* pSource);
	bool checkValidValue(const string& strKey, MyKey curKey);

	static USERDATA nodeToUSERDATA(MyNode& node);
	void notifyAll();

protected:
	MyFile(const string& fileName, MyList& list);
	~MyFile(void);
private:
	string fileName;
	MyList& list;
};