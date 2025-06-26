#include <iostream>
using namespace std;

class Base
{
public:
	Base() : State(0) {}
	Base(int i) : State(i) {}

	virtual int Dummy()
	{
		cout << "Base Dummy" << endl;
		return State;
	}
private:
	int State;
};

class Derived : public Base
{
public:
	Derived(int i = 0) : Base(i) {}
	void SetNumber(int i) { Number = i; }

	int Number;
};

int main()
{
	Derived* PD;
	Base* PBA = new Derived(23);

	// Base 타입의 객체를 Derived 객체로 변환
	// 업캐스팅 된것을 다시 되돌려놓는 것
	PD = dynamic_cast<Derived*>(PBA);
	if (PD == nullptr) std::cout << "첫 번째 PBA 객체의 변환이 실패함" << std::endl;

	PD->SetNumber(10);
	std::cout << PD->Number << std::endl;
	std::cout << PD->Dummy() << std::endl;
	delete PBA;

	Base* PBB = new Base(568);
	PD = dynamic_cast<Derived*>(PBB);
	if (PD == nullptr) std::cout << "두 번째 PBB 객체의 변환이 실패함" << std::endl;

	// static_cast를 통해 정상 작동하는 것처럼 보이나 실제 다른 영역을 침범하여 작업이 이루어진다.
	PD = static_cast<Derived*>(PBB);
	PD->SetNumber(110);
	std::cout << PD->Number << std::endl;
	std::cout << PD->Dummy() << std::endl;
	delete PBB;

	return 0;
}