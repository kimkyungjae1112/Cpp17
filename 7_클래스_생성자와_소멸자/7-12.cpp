#include <iostream>

class MyString
{
	MyString(const char* N = nullptr);
	MyString(const MyString& Other);
	MyString(MyString&& Other) noexcept; // 이동 생성자 선언
	~MyString();

	MyString& operator=(const MyString& Other);
	MyString& operator=(MyString&& Other) noexcept;

	void SetString(const char* N);
	const char* GetString() const;
	int GetLength() const;

private:
	char* cData;
	int iLength;
};

MyString::MyString(MyString&& Other) noexcept
	: cData(Other.cData), iLength(Other.iLength)
{
	Other.cData = nullptr;
	Other.iLength = 0;
}

MyString& MyString::operator=(MyString&& Other) noexcept
{
	if (this != &Other)
	{
		std::swap(this->cData, Other.cData);
		std::swap(this->iLength, Other.iLength);
	}

	return *this;
}