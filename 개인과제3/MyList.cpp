#include <iostream>
#include "MyList.h"
#include "UserData.h"

using namespace std;

MyList::MyList()
{
	pHead = new UserData("Dummy", "Head", "Data");
	pTail = new UserData("Dummy", "Tail", "Data");
	pHead->pPrev = nullptr;
	pHead->pNext = pTail;
	pTail->pPrev = pHead;
	pTail->pNext = nullptr;
}

MyList::~MyList(void)
{
	releaseList();
}

void MyList::releaseList(void)
{
	MyNode* pDelete = nullptr;
	for (MyNode& node : *this) {
		pDelete = node.pPrev;
		delete pDelete;
	}
	delete this->pTail->pPrev;
	delete this->pTail;
}




MyIterator MyList::begin() const
{ 
	return MyIterator(pHead->pNext);
}

MyIterator MyList::end() const
{ 
	return MyIterator(pTail);
}


MyNode* MyList::addNewNode(MyNode* pNewNode)
{

	if (findNode(pNewNode->getKey(), MyKey::Phone) != nullptr) {
		delete pNewNode;
		return nullptr;
	}

	if (onAddNewNode(pNewNode)) {
		pNewNode->pPrev = pTail->pPrev;
		pNewNode->pNext = pTail;
		pTail->pPrev->pNext = pNewNode;
		pTail->pPrev = pNewNode;
		notifyAllObservers();
		return pNewNode;
	}


	throw 3;
}

MyNode* MyList::findNode(const string& strKey, MyKey key)
{
	for (MyNode& node : *this) {
		if (node.getKey() == strKey)
			return &node;
	}
	return nullptr;
}
int MyList::getListCounter(void)
{
	int cnt = 0;
	for (MyNode& node : *this) {
		cnt++;
	}
	return cnt;
}

int MyList::removeNode(const string& strKey)
{
	for (MyNode& node : *this) {
		if (node.getKey() == strKey) {
			node.pPrev->pNext = node.pNext;
			node.pNext->pPrev = node.pPrev;
			delete &node;
			notifyAllObservers();
			return 1;
		}
	}
	return 0;
}

int MyList::onAddNewNode(MyNode* pNewNode)
{
	return 1;
}
