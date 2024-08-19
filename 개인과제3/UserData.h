#pragma once
#include <string>
#include "MyNode.h"
#include "MyKey.h"

using std::string;

class UserData : public MyNode
{
	friend class MyList;
	friend class MyFile;
public:
	UserData(void);
	UserData(const string& strName, const string& straAddress, const string& strPhone);
	~UserData(void);

	const string& getName(void) const { return strName;}
	const string& getAddress(void) const { return strAddress; }
	const string& getPhone(void) const { return strPhone; }

	void setName(const string& strName) { this->strName = strName; }
	void setAddress(const string& strAddress) { this->strAddress = strAddress; }
	void setPhone(const string& strPhone) { this->strPhone = strPhone; }

	const string& getSearchKey(const MyKey key);

	//friend std::ofstream& operator<<(std::ofstream& ofs, const UserData& userData);
	//friend std::ifstream& operator>>(std::ifstream& ifs, UserData& userData);


	virtual const string& getKey(void);
	virtual void printNode(void);

protected:
	string strName;
	string strAddress;
	string strPhone;

private:
	static void writeString(std::ofstream& ofs, const string& str);
	static string readString(std::ifstream& ifs);
};