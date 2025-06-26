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

	// 2. �Լ��� Ŭ������ �ν��Ͻ��� ���� ������ ����� ����� ������ ������
	//    ��ü�� ��ȯ�ϴ� ��쿡 ���� ������ �Ǵ� �̵� �������� ȣ���� �����ȴ�.
	MyString obj1(Fun123("Fun123()"));

	// 3. �Լ��� ������ ���� ���� Ŭ������ �ν��Ͻ��� �����Ͽ� ��ȯ�ϴ� ��쿡
	//    ���� ������ �Ǵ� �̵� �������� ȣ���� �����ȴ�.
	MyString obj2(Gun123("Gun123()"));

	// 1. �ʱ�ȭ ����Ʈ�� ����Ͽ� ��ü�� �����ϴ� ��쿡 �̵� �����ڰ� �����ȴ�.
	MyString xyz = "Return Value Optimization";

	std::cout << "���� ������, �̵� ������, �̵� ���� ������ �Ҹ� Ƚ�� : " << Count << std::endl;
}