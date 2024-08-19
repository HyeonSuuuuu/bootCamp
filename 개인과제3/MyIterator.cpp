#include "MyIterator.h"

MyIterator::MyIterator(void)
	: pCurrent(nullptr)
{
}

MyIterator::MyIterator(MyNode* pCurrent)
	: pCurrent(pCurrent)
{
}


MyIterator::~MyIterator(void)
{
}

MyNode* MyIterator::GetCurrent(void) const 
{ return pCurrent;
}

void MyIterator::MoveNext(void)
{
	if (pCurrent != nullptr)
		pCurrent = pCurrent->getNext();
}


MyNode& MyIterator::operator*() const
{ return *pCurrent; 
}

MyIterator& MyIterator::operator++()
{
	this->MoveNext();
	return *this;
}

bool MyIterator::operator==(const MyIterator& other) const
{
	return pCurrent == other.pCurrent;
}

bool MyIterator::operator!=(const MyIterator& other) const {
	return pCurrent != other.pCurrent;
}