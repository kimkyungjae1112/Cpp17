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
	Base& Br = D; // 참조를 사용하여 상위 Base 클래스의 객체로 변환한다.

	// 하위 클래스의 객체로 변환할 때 다음과 같은 명시적 변환도 허용은 된다.
	// Derived& Another_D = (Derived&) Br;
	Derived& Another_D = static_cast<Derived&>(Br);
	printf("D = %p, Br = %p, Another_D = %p\n", &D, &Br, &Another_D);

	Derived A[10];
	Base* DP = static_cast<Base*>(A); // 업캐스팅
	
	return 0;
}