#include <iostream>
#include <fstream>
#include "UserData.h"

using namespace std;

UserData::UserData(void)
{
}

UserData::UserData(const string& strName, const string& strAddress, const string& strPhone)
	: strName(strName), strAddress(strAddress), strPhone(strPhone)
{
}


UserData::~UserData(void)
{
}

const string& UserData::getKey(void)
{
	return this->strPhone;
}

void UserData::printNode(void)
{
	if (this->getDelete()) {
		cout << "[Delete] ";
	} 
	else if (this->getNew())
		cout << "[New] ";

#ifdef _DEBUG
	cout << "<" << getOffset() << ">" << "[" << this << "] " << strName << '\t' << strAddress << '\t' << strPhone << " [" << getNext() << "]" << endl;
#else
	cout << strName << '\t' << strAddress << '\t' << strPhone << endl;
#endif
}

const string& UserData::getSearchKey(const MyKey key)
{
	switch (key) {
	case MyKey::Name:
		return strName;
	case MyKey::Address:
		return strAddress;
	case MyKey::Phone:
		return strPhone;
	default:
		return "";
	}
}




































//ofstream& operator<<(ofstream& ofs, const UserData& userData)
//{
//	bool bEmpty = false;
//	ofs.write(reinterpret_cast<const char*>(&bEmpty), sizeof(bEmpty));
//	UserData::writeString(ofs, userData.strName);
//	UserData::writeString(ofs, userData.strAddress);
//	UserData::writeString(ofs, userData.strPhone);
//	return ofs;
//}
//ifstream& operator>>(ifstream& ifs, UserData& userData)
//{
//	
//	bool bEmpty;
//	ifs.read(reinterpret_cast<char*>(&bEmpty), sizeof(bEmpty));
//
//	if (bEmpty) {
//		UserData::readString(ifs);
//		UserData::readString(ifs);
//		UserData::readString(ifs);
//		userData.strName = "";
//		userData.strAddress = "";
//		userData.strPhone = "";
//	}
//	else {
//		userData.strName = UserData::readString(ifs);
//		userData.strAddress = UserData::readString(ifs);
//		userData.strPhone = UserData::readString(ifs);
//	}
//	return ifs;
//}
//
//
//void UserData::writeString(std::ofstream& ofs, const string& str)
//{
//	size_t length = str.size();
//	ofs.write(reinterpret_cast<const char*>(&length), sizeof(length));
//	ofs.write(str.c_str(), length);
//}
//string UserData::readString(std::ifstream& ifs)
//{
//	size_t length;
//	ifs.read(reinterpret_cast<char*>(&length), sizeof(length));
//	string str(length, ' ');
//	ifs.read(&str[0], length);
//	return str;
//}