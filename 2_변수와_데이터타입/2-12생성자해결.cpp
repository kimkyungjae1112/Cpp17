#pragma warning(disable : 4996) //윈도우라면 이 문장을 추가시켜 준다.
#include <iostream>
#include <cstdio>
#include <cstring>

struct Data
{
	// 아래와 같이 사용자 정의 생성자를 정의한다.
	Data(int a, const char* n, int b)
	{
		age = a;
		strcpy(name, n);
		balance = b;
	}

	//컴파일러는 기본으로 아래와 같은 디폴트 생성자를 자동 제공해준다.
	Data()
	{
		age = 0;
		memset(name, 0, 100);
		balance = 0;
	}

	int age; //나이
	char name[100]; //이름
	int balance; //지갑 속의 용돈
};

struct Test
{
	//Test() {}
	int a;
};

void Print(Data user)
{
	std::cout << user.age << ", " << user.name << ", 잔액 : " << user.balance << std::endl;
}

void Print(Test test)
{
	std::cout << test.a << std::endl;
}

int main()
{
	Data user02(33, "이순신", 2000);
	Data user04 = Data(45, "이성계", 3000);
	Data* user05 = new Data(60, "연개소문", 45000);
	Data user08;
	Data* user_08 = new Data;

	Print(user02);
	Print(user04);
	Print(*user05);
	Print(user08);
	Print(*user_08);
	
	Test test;
	Print(test);
}