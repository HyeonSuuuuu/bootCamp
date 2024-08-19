#include <iostream>
#include "MyString.h"

using namespace std;

void MyString::setData(const char* pParam)
{
	onSetData(pParam);
	if (pszData != nullptr)
		delete[] pszData;
	size_t length = strlen(pParam);
	pszData = new char[length + 1];

	strcpy_s(pszData, length + 1, pParam);

	this->length = length;
}

MyString::MyString() {
	cout << "MyString()" << endl;
}

MyString::MyString(const char* param) {
	cout << "MyString(const char*)" << endl;
	this->setData(param);
}

MyString::MyString(const MyString& rhs) {
	cout << "MyString(const MyString&)" << endl;
	this->setData(rhs.getData());
}

MyString::MyString(MyString&& rhs) noexcept{
	cout << "MyString(const MyString&&)" << endl;
	this->setData(rhs.getData());
}

MyString::~MyString() {
	cout << "~MyString()" << endl;
	delete[] pszData;
}

const char* MyString::getData() const {
	return  pszData;
}

size_t MyString::getLength() const {
	return length;
}

MyString& MyString::operator=(MyString&& rhs) noexcept
{
	cout << "operator=(MyString&&)" << endl;
	this->pszData = rhs.pszData;
	rhs.pszData = nullptr;
	return *this;
}

MyString MyString::operator+(const MyString& rhs)
{
	MyString result(pszData);
	result.append(rhs.getData());
	return result;
}


size_t MyString::append(const char* pParam)
{
	if (pParam == nullptr) {
		return 0;
	}
	if (pszData == nullptr) {
		this->setData(pParam);
		return this->length;
	}
	else {
		size_t lenAppend = strlen(pParam);
		char* pResult = new char[length + lenAppend + 1];

		strcpy_s(pResult, length + lenAppend + 1, pszData);
		strcat_s(pResult + length, lenAppend + 1, pParam);

		delete[] pszData;
		pszData = pResult;
		length += lenAppend;
	}
	return length;
}


MyString& MyString::operator+=(const char* pParam)
{
	this->append(pParam);
	return *this;
}

char MyString::operator[](int index) const
{
	if (index < 0 || index >= length)
		return 0;

	if (pszData != nullptr)
		return pszData[index];

	return 0;
}

MyString operator+(const char* pLeft, const MyString& rhs) 
{
	MyString result(pLeft);
	result.append(rhs.pszData);
	return result;
}

MyString MyString::operator+(const char* rhs)
{
	MyString result(pszData);
	result.append(rhs);
	return result;
}