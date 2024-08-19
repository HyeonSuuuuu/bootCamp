#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include "MyFile.h"
#include "MyList.h"
#include "MyKey.h"
#include "UserData.h"

using namespace std;

MyFile::MyFile(const string& fileName, MyList& list)
	: fileName(fileName), list(list)
{
}

MyFile::~MyFile(void)
{
}


size_t MyFile::getEmptyOffset()
{
	static int nCnt = -1;
	FILE* fp = NULL;
	fopen_s(&fp, fileName.c_str(), "rb");
	if (fp == NULL)
		return NULL;
	USERDATA_WITH_FLAG userWithFlag = { 0 };
	size_t offset = 0;
	while (fread(&userWithFlag, sizeof(USERDATA_WITH_FLAG), 1, fp) > 0) {
		if (userWithFlag.bEmpty) {
			fclose(fp);
			return offset;
		}
		fseek(fp, ++offset * sizeof(USERDATA_WITH_FLAG), SEEK_SET);
	}
	fclose(fp);
	nCnt++;
	return offset + nCnt;
}

size_t MyFile::countFileData()
{
	FILE* fp = NULL;
	fopen_s(&fp, fileName.c_str(), "rb");
	if (fp == NULL)
		return NULL;

	USERDATA_WITH_FLAG userWithFlag = { 0 };
	size_t offset = 0;
	while (fread(&userWithFlag, sizeof(USERDATA_WITH_FLAG), 1, fp) > 0) {
		fseek(fp, ++offset * sizeof(USERDATA_WITH_FLAG), SEEK_SET);
	}
	fclose(fp);
	return offset;
}

bool MyFile::checkValidValue(const string& strKey, MyKey curKey)
{
	MyNode* node = searchFile(strKey, curKey);
	if (node == nullptr)
		return true;
	else
		return false;
}

MyNode* MyFile::searchFile(const string& strKey, MyKey curKey)
{
	FILE* fp = NULL;
	fopen_s(&fp, fileName.c_str(), "rb");
	if (fp == NULL)
		return NULL;

	USERDATA_WITH_FLAG userWithFlag = { 0 };
	size_t offset = 0;
	MyNode* result;

	while (fread(&userWithFlag, sizeof(USERDATA_WITH_FLAG), 1, fp) > 0) {
		UserData user(userWithFlag.userData.name, userWithFlag.userData.address, userWithFlag.userData.phone);
		if (!userWithFlag.bEmpty) {
			if (user.getSearchKey(curKey) == strKey) {
				fclose(fp);
				if (list.addNewNode(new UserData(user))) {
					result = list.getEndNode();
					result->setNew(false);
					result->setOffset(offset);
					return list.getEndNode();
				}
				else {
					throw 3;
				}
			}
		}
		fseek(fp, ++offset * sizeof(USERDATA_WITH_FLAG), SEEK_SET);
	}
	fclose(fp);
	return NULL; 
}

void MyFile::notifyAll()
{
	notifyAllObservers();
}

int MyFile::saveNodeToFile(MyNode& node)
{
	//if (pNode->pDataCache == NULL || pNode->sizeOfData == 0)
	//	return 0;

	FILE* fp = NULL;
	fopen_s(&fp, fileName.c_str(), "r+");
	if (fp == NULL)
		return 0;

	fseek(fp, node.getOffset() * sizeof(USERDATA_WITH_FLAG), SEEK_SET);
	USERDATA_WITH_FLAG userDataWithFlag;
	userDataWithFlag.bEmpty = node.getDelete();
	USERDATA user = nodeToUSERDATA(node);
	if (1 != userDataCopy(&userDataWithFlag.userData, &user)) {
		return 0;
	}
	if (fwrite(&userDataWithFlag, sizeof(USERDATA_WITH_FLAG), 1, fp) > 0) {
		fclose(fp);
		node.setNew(false);
		return 1;
	}
	return 0;
}

int MyFile::saveNewDataToFile(void)
{
	USERDATA_WITH_FLAG pDataWithFlag;
	for (MyNode & node : list) {
		if (node.getNew()) {
			saveNodeToFile(node);
		}
	}
	notifyAllObservers();
	return 1;
}



int MyFile::userDataCopy(USERDATA* pDestination, const USERDATA* pSource)
{
	if (0 != strcpy_s(pDestination->name, strlen(pSource->name) + 1, pSource->name))
		return 0;
	if (0 != strcpy_s(pDestination->address, strlen(pSource->address) + 1, pSource->address))
		return 0;
	if (0 != strcpy_s(pDestination->phone, strlen(pSource->phone) + 1, pSource->phone))
		return 0;
	return 1;
}


void MyFile::printAll(size_t maxOutput) const
{
	FILE* fp = NULL;
	fopen_s(&fp, fileName.c_str(), "rb");
	if (fp == NULL)
		return;

	USERDATA_WITH_FLAG userWithFlag = { 0 };
	size_t offset = 0;
	size_t cnt = 0;
	char ch;
	while (fread(&userWithFlag, sizeof(USERDATA_WITH_FLAG), 1, fp) > 0) {
		if (!userWithFlag.bEmpty) {
			printf("<%d>%s\t%s\t%s\n", offset, userWithFlag.userData.name, userWithFlag.userData.address, userWithFlag.userData.phone);

			if (!(++cnt % maxOutput)) {
				printf("Press any key to continue or 'q' to exit...");
				if (_getch() == 'q')
					break;
			}
		}
		
		fseek(fp, ++offset * sizeof(USERDATA_WITH_FLAG), SEEK_SET);
	}
	fclose(fp);
}


const char* USERDATA::getSearchKey(const MyKey key)
{
	switch (key) {
	case MyKey::Name:
		return name;
	case MyKey::Address:
		return address;
	case MyKey::Phone:
		return phone;
	default:
		return "";
	}
}


USERDATA MyFile::nodeToUSERDATA(MyNode& node)
{
	USERDATA user;
	UserData& userData = static_cast<UserData&>(node);
	strcpy_s(user.name, strlen(userData.getName().c_str()) + 1, userData.getName().c_str());
	strcpy_s(user.address, strlen(userData.getAddress().c_str()) + 1, userData.getAddress().c_str());
	strcpy_s(user.phone, strlen(userData.getPhone().c_str()) + 1, userData.getPhone().c_str());
	return user;
}