#pragma once
#include "MyNode.h"


class MyIterator
{
	friend class MyList;

public:
	MyIterator();
	MyIterator(MyNode* pCurrent);
	~MyIterator();
	


	MyNode* GetCurrent(void) const;
	void MoveNext(void);

	MyNode& operator*() const;
	MyIterator& operator++();
	bool operator==(const MyIterator& other) const;
	bool operator!=(const MyIterator& other) const;


private: 
	MyNode* pCurrent;
};