#pragma warning(disable : 4996) //�������� �� ������ �߰����� �ش�.
#include <iostream>
#include <cstdio>
#include <cstring>

struct Data
{
	// �Ʒ��� ���� ����� ���� �����ڸ� �����Ѵ�.
	Data(int a, const char* n, int b)
	{
		age = a;
		strcpy(name, n);
		balance = b;
	}

	//�����Ϸ��� �⺻���� �Ʒ��� ���� ����Ʈ �����ڸ� �ڵ� �������ش�.
	Data()
	{
		age = 0;
		memset(name, 0, 100);
		balance = 0;
	}

	int age; //����
	char name[100]; //�̸�
	int balance; //���� ���� �뵷
};

struct Test
{
	//Test() {}
	int a;
};

void Print(Data user)
{
	std::cout << user.age << ", " << user.name << ", �ܾ� : " << user.balance << std::endl;
}

void Print(Test test)
{
	std::cout << test.a << std::endl;
}

int main()
{
	Data user02(33, "�̼���", 2000);
	Data user04 = Data(45, "�̼���", 3000);
	Data* user05 = new Data(60, "�����ҹ�", 45000);
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