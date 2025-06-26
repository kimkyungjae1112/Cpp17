#include <iostream>
using namespace std;

class Base
{
public:
	virtual void Dummy()
	{
		cout << "Base Dummy" << endl;
	}
};

class Derived : public Base
{
public:
	Derived(int i = 0) : Number(i) {}

private:
	int Number;
};

int main()
{
	Derived D;
	Base& Br = D; // ������ ����Ͽ� ���� Base Ŭ������ ��ü�� ��ȯ�Ѵ�.

	// ���� Ŭ������ ��ü�� ��ȯ�� �� ������ ���� ����� ��ȯ�� ����� �ȴ�.
	// Derived& Another_D = (Derived&) Br;
	Derived& Another_D = static_cast<Derived&>(Br);
	printf("D = %p, Br = %p, Another_D = %p\n", &D, &Br, &Another_D);

	Derived A[10];
	Base* DP = static_cast<Base*>(A); // ��ĳ����
	
	return 0;
}