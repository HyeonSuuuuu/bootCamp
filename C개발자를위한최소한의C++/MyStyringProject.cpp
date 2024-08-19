#include <iostream>
#include "MyString.h"
#include "MyStringEx.h"
using namespace std;


MyString getHello()
{
	MyString hello;
	hello.setData("Hello");
	return hello;
}

//int main()
//{
//	MyStringEx* pstrData = new MyStringEx;
//	pstrData->setData("ธÛธÛภฬพฦต้");
//	cout << pstrData->getData() << endl;
//
//	delete pstrData;
//}