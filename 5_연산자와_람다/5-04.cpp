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
		printf("계좌 : %s, 소유자 : %s", AccountNum, Name);
		printf(", 잔액 : %i\n", Balance);
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

	//문자열 크기와 마지막에 '\0'를 포함해야 하므로 strlen() 함수가 반환되는 값에
	//1을 추가해줘야 한다.
	char* NewId = new(std::nothrow) char[strlen(Id) + 1];
	if (NewId == nullptr) return nullptr;

	strcpy(NewId, Id);
	Temp->AccountNum = NewId;

	char* NewName = new(std::nothrow) char[strlen(Name) + 1];
	if (NewName == nullptr) return nullptr;

	strcpy(NewName, Name);
	Temp->Name = NewName;
	Temp->Balance = Bal;
	std::cout << "Account 객체를 생성하였습니다." << std::endl;
	return Temp;
}

int CloseAcct(Account* Acct)
{
	std::cout << "Account 객체를 삭제하였습니다." << std::endl;

	delete[] Acct->AccountNum;
	delete[] Acct->Name;
	delete Acct;
	return 1;
}

int main()
{
	Account* Hong = OpenAcct("120-345-12909", "홍길동", 60000);
	if (Hong == nullptr) return -1;

	Account* Kim = OpenAcct("129-345-929100", "김홍도", 0);
	if (Kim == nullptr) return -1;


	// 홍길동의 계좌에서 돈을 빼서 김홍도의 계좌로 이체한다.
	Hong->WithDraw(2000);
	Kim->Deposit(2000);
	Hong->Print();
	Kim->Print();

	CloseAcct(Hong);
	CloseAcct(Kim);

	return 0;
}