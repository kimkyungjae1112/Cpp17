#include <iostream>
#include <string>
#include <algorithm>

int Count = 0;

class MyString
{
public:
	MyString(const char* ptr = nullptr) : sData(ptr)
	{
		std::cout << "Constructor : " << ptr << std::endl;
	}
	MyString(const MyString& Other) : sData(Other.sData)
	{
		std::cout << "Copy Constructor : " << sData.c_str() << std::endl;
		++Count;
	}
	MyString(MyString&& Other) noexcept
	{
		std::swap(this->sData, Other.sData);
		std::cout << "Move Constructor : " << sData.c_str() << std::endl;
		++Count;
	}
	~MyString()
	{
		std::cout << "Destructor : " << sData.c_str() << std::endl;
	}

	MyString& operator=(const MyString& Other)
	{
		if (this != &Other)
		{
			sData = Other.sData;
		}
		printf("MyString& MyString::operator = (MyString& %s\n ", this->sData);
		++Count;
		return *this;
	}
	MyString& operator=(MyString&& Other) noexcept
	{
		if (this != &Other)
		{
			std::swap(sData, Other.sData);
		}
		printf("MyString& MyString::operator = (MyString&& %s\n ", this->sData);
		++Count;
		return *this;
	}

private:
	std::string sData;
};

MyString Fun123(const char* ptr = nullptr)
{
	MyString obj(ptr);
	return obj;
}
MyString Gun123(const char* ptr = nullptr)
{
	return MyString(ptr);
}

void Foo(const char* ptr = nullptr)
{
	throw MyString(ptr);
}

int main()
{
	MyString abc("abc");

	// 2. 함수가 클래스의 인스턴스를 지역 변수로 만들어 사용한 다음에 값으로
	//    객체를 반환하는 경우에 복사 생성자 또는 이동 생성자의 호출이 생략된다.
	MyString obj1(Fun123("Fun123()"));

	// 3. 함수가 다음과 같이 무명 클래스의 인스턴스를 생성하여 반환하는 경우에
	//    복사 생성자 또는 이동 생성자의 호출이 생략된다.
	MyString obj2(Gun123("Gun123()"));

	// 1. 초기화 리스트를 사용하여 객체를 생성하는 경우에 이동 생성자가 생략된다.
	MyString xyz = "Return Value Optimization";

	std::cout << "복사 생성자, 이동 생성자, 이동 대입 연산자 불린 횟수 : " << Count << std::endl;
}