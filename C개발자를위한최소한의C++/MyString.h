#pragma once


class MyString
{
	friend MyString operator+(const char* pLeft, const MyString& rhs);
public:
	MyString();
	explicit MyString(const char* param);
	MyString(const MyString& rhs);
	MyString(MyString&& rhs) noexcept;
	virtual ~MyString();

	MyString& operator=(const MyString& rhs) {
		this->setData(rhs.getData());
		return *this;
	}
	MyString& operator=(const char* pszData) {
		this->setData(pszData);
		return *this;
	}
	MyString& operator=(MyString&& rhs) noexcept;
	operator const char* () const {
		return pszData;
	}

	MyString operator+(const MyString& rhs);
	MyString operator+(const char* rhs);
	MyString& operator+=(const char* pParam);
	char operator[](int index) const;

	const char* getData() const;
	void setData(const char* pParam);
	virtual void onSetData(const char*& pParam) {

	}

	size_t getLength() const;
	size_t append(const char* pParam);
private:
	char* pszData = nullptr;
	size_t length = 0;
};

