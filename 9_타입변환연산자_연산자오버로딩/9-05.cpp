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

	// Base Ÿ���� ��ü�� Derived ��ü�� ��ȯ
	// ��ĳ���� �Ȱ��� �ٽ� �ǵ������� ��
	PD = dynamic_cast<Derived*>(PBA);
	if (PD == nullptr) std::cout << "ù ��° PBA ��ü�� ��ȯ�� ������" << std::endl;

	PD->SetNumber(10);
	std::cout << PD->Number << std::endl;
	std::cout << PD->Dummy() << std::endl;
	delete PBA;

	Base* PBB = new Base(568);
	PD = dynamic_cast<Derived*>(PBB);
	if (PD == nullptr) std::cout << "�� ��° PBB ��ü�� ��ȯ�� ������" << std::endl;

	// static_cast�� ���� ���� �۵��ϴ� ��ó�� ���̳� ���� �ٸ� ������ ħ���Ͽ� �۾��� �̷������.
	PD = static_cast<Derived*>(PBB);
	PD->SetNumber(110);
	std::cout << PD->Number << std::endl;
	std::cout << PD->Dummy() << std::endl;
	delete PBB;

	return 0;
}