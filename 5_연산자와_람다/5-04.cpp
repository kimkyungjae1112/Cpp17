#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>

struct Account
{
	char* AccountNum;
	char* Name;
	int Balance;

	void Print()
	{
		printf("���� : %s, ������ : %s", AccountNum, Name);
		printf(", �ܾ� : %i\n", Balance);
	}

	void Deposit(int Money)
	{
		Balance += Money;
	}

	void WithDraw(int Money)
	{
		Balance -= Money;
	}
};

Account* OpenAcct(const char* Id, const char* Name, int Bal)
{
	Account* Temp = new(std::nothrow) Account();
	if (Temp == nullptr) return nullptr;

	//���ڿ� ũ��� �������� '\0'�� �����ؾ� �ϹǷ� strlen() �Լ��� ��ȯ�Ǵ� ����
	//1�� �߰������ �Ѵ�.
	char* NewId = new(std::nothrow) char[strlen(Id) + 1];
	if (NewId == nullptr) return nullptr;

	strcpy(NewId, Id);
	Temp->AccountNum = NewId;

	char* NewName = new(std::nothrow) char[strlen(Name) + 1];
	if (NewName == nullptr) return nullptr;

	strcpy(NewName, Name);
	Temp->Name = NewName;
	Temp->Balance = Bal;
	std::cout << "Account ��ü�� �����Ͽ����ϴ�." << std::endl;
	return Temp;
}

int CloseAcct(Account* Acct)
{
	std::cout << "Account ��ü�� �����Ͽ����ϴ�." << std::endl;

	delete[] Acct->AccountNum;
	delete[] Acct->Name;
	delete Acct;
	return 1;
}

int main()
{
	Account* Hong = OpenAcct("120-345-12909", "ȫ�浿", 60000);
	if (Hong == nullptr) return -1;

	Account* Kim = OpenAcct("129-345-929100", "��ȫ��", 0);
	if (Kim == nullptr) return -1;


	// ȫ�浿�� ���¿��� ���� ���� ��ȫ���� ���·� ��ü�Ѵ�.
	Hong->WithDraw(2000);
	Kim->Deposit(2000);
	Hong->Print();
	Kim->Print();

	CloseAcct(Hong);
	CloseAcct(Kim);

	return 0;
}