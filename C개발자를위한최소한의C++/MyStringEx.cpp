#include <iostream>
#include "MyStringEx.h"

using namespace std;





MyStringEx::MyStringEx()
{
	cout << "MyStringEx()" << endl;
}
MyStringEx::~MyStringEx()
{
	cout << "~MyStringEx()" << endl;
}

//void MyStringEx::setData(const char* pParam)
//{
//	cout << "setData()" << endl;
//	if (pParam != nullptr) {
//		if (strcmp(pParam, "�۸��̾Ƶ�") == 0) {
//			MyString::setData("�׳ɾƵ�");
//			return;
//		}
//	}
//
//	MyString::setData(pParam);
//}
void MyStringEx::onSetData(const char*& pParam)
{
	MyString::onSetData(pParam);

	cout << "MyStringEx::onSetData()" << endl;
	if (pParam != nullptr) {
		if (strcmp(pParam, "�۸��̾Ƶ�") == 0) {
			pParam = "�츮�Ϳ��";
		}
	}
}