#pragma once
#include <iostream>



class UserData {

	UserData(void) {
		nUserDataCounter++;
	}
	UserData(int age, std::string name, std::string phone) {
		this->age = age;
		this->name = name;
		this->phone = phone;
		nUserDataCounter++;
	}
	~UserData(void) {
		nUserDataCounter--;
	}

	std::string getName(void) const {
		return name;
	}

	std::string getPhone(void) const {
		return phone;
	}
	int getAge(void) const {
		return age;
	}
private:
	int age;
	std::string name;
	std::string phone;
	UserData* pNext = nullptr;
	UserData* pPrev = nullptr;
	static int nUserDataCounter;
};