#pragma once
#include <string>


class MyNode
{
	friend class MyList;
public:
	MyNode(void);
	virtual ~MyNode(void);

	MyNode* getNext(void) const { return pNext; }
	MyNode* getPrev(void) const { return pPrev; }
	bool getNew(void) const { return bNew; }
	void setNew(bool bNew) { this->bNew = bNew; }
	bool getDelete(void) const { return bDelete; }
	void setDelete(bool bDelete) { this->bDelete = bDelete; }
	size_t getOffset(void) const { return offset; }
	void setOffset(size_t offset) { this->offset = offset; }

	virtual const std::string& getKey(void) = 0;
	virtual void printNode(void) = 0;

private:
	bool bNew = true;
	bool bDelete = false;
	size_t offset = 0;
	MyNode* pNext;
	MyNode* pPrev;
};