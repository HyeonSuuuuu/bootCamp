#pragma once
#include <string>
#include "MyNode.h"
#include "MyIterator.h"
#include "MyKey.h"
#include "Observer.h"
using std::string;


class MyList : public Observable
{

public:
	static MyList& get() {
		static MyList* list = new MyList();
		return *list;
	}

	MyList(const MyList&) = delete;
	MyList(MyList&&) = delete;
	MyList& operator=(const MyList&) = delete;
	MyList& operator=(MyList&&) = delete;

	MyIterator begin() const;
	MyIterator end() const;

	MyNode* findNode(const string& strKey, MyKey key);
	MyNode* addNewNode(MyNode* pNewNode);
	int removeNode(const string& strKey);
	MyNode* getEndNode(void) { return pTail->pPrev; }
	int getListCounter(void);

	virtual int onAddNewNode(MyNode* pNewNode);
protected:
	MyList();
	~MyList(void);
	MyNode* pHead;
	MyNode* pTail;
	void releaseList(void);
};