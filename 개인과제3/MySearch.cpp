#include <regex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "MySearch.h"
#include "MyList.h"
#include "MyFile.h"
#include "UserData.h"

using namespace std;

MySearch::MySearch(MyList& rList, MyFile& rFile)
	: list(rList), file(rFile)
{
}

MySearch::~MySearch()
{
}

MyKey MySearch::stringToMyKey(const string& key)
{
	if (key == "Name" || key == "name" || key == "이름") {
		return MyKey::Name;
	}
	else if (key == "Address" || key == "address" || key == "주소") {
		return MyKey::Address;
	}
	else if (key == "Phone" || key == "phone" || key == "전화번호") {
		return MyKey::Phone;
	}
	else {
		throw 4;
	}
}

void MySearch::parse(string& input)
{
	std::regex regex_pattern(R"((name|phone|address|이름|전화번호|주소|Name|Phone|Address)=["']([^"']+)["']\s*(and|or)?)");

	std::smatch matches;
	std::string::const_iterator searchStart(input.cbegin());

	int cnt = 0;
	std::string logic;
	std::string key;
	std::string value;
	while (std::regex_search(searchStart, input.cend(), matches, regex_pattern)) {
		// Key와 Value 출력
		if (++cnt == 1) {
			key = matches[1].str();
			value = matches[2].str();
			findNodeAll(value, stringToMyKey(key));
			searchFileAll(value, stringToMyKey(key));
		}
		else {
			if (!logic.empty()) {
				if (logic == "or" || logic == "OR") {
					key = matches[1].str();
					value = matches[2].str();
					findNodeAll(value, stringToMyKey(key));
					searchFileAll(value, stringToMyKey(key));
				}
				else if (logic == "and" || logic == "AND") {
					key = matches[1].str();
					value = matches[2].str();
					findSearchListAll(value, stringToMyKey(key));
				}
			}
		}
		logic = matches[3].str();
		// 다음 매칭을 위해 검색 시작 위치를 갱신
		searchStart = matches.suffix().first;
	}
}


void MySearch::findSearchListAll(const string& strKey, MyKey key)
{
	for (int i = 0; i < searchList.size(); ++i) {
		if (searchList[i].getSearchKey(key) != strKey) {
			searchList.erase(searchList.begin() + i);
			--i;
		}
	}
}

bool MySearch::checkValidOffset(UserData& user)
{
	for (int i = 0; i < searchList.size(); ++i) {
		if (searchList[i].getOffset() == user.getOffset()) {
			return 0;
		}
	}
	return 1;
}

void MySearch::findNodeAll(const string& strKey, MyKey key)
{
	for (MyNode& node : list) {
		UserData& user = static_cast<UserData&>(node);
		if (user.getSearchKey(key) == strKey) {
			searchList.push_back(static_cast<UserData&>(node));
		}
	}
}


void MySearch::searchFileAll(const string& strKey, MyKey curKey)
{
	FILE* fp = NULL;
	fopen_s(&fp, file.getFileName().c_str(), "rb");
	if (fp == NULL)
		return;

	USERDATA_WITH_FLAG userWithFlag = { 0 };
	size_t offset = 0;
	MyNode* result;
	UserData user;
	while (fread(&userWithFlag, sizeof(USERDATA_WITH_FLAG), 1, fp) > 0) {
		user.setAddress(userWithFlag.userData.address);
		user.setName(userWithFlag.userData.name);
		user.setPhone(userWithFlag.userData.phone);
		if (!userWithFlag.bEmpty) {
			if (user.getSearchKey(curKey) == strKey) {
				if (checkValidOffset(user)) {
					user.setOffset(offset);
					searchList.push_back(user);
				}
			}
		}
		fseek(fp, ++offset * sizeof(USERDATA_WITH_FLAG), SEEK_SET);
	}
	fclose(fp);
}