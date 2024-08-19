#pragma once
#include "MyString.h"
class MyStringEx : public MyString
{
public:
	MyStringEx();
	~MyStringEx();
	// void setData(const char* pParam);
	virtual void onSetData(const char*& pParam);

	MyStringEx& operator=(const char* pszData) {
		this->setData(pszData);
		return *this;
	}
};

