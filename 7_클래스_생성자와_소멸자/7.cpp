#include <iostream>

class Simple
{
private:
	int Num1;
	int Num2;

public:
	Simple() = default;
	Simple(int N1, int N2) :Num1(N1), Num2(N2)
	{
		std::cout << "�⺻ ������ ȣ��" << std::endl;
	}

	// ���� ������ : ���� ���� ����
	Simple(const Simple& Copy) : Num1(Copy.Num1), Num2(Copy.Num2)
	{
		std::cout << "���� ������ ȣ��" << std::endl;
	}

	Simple& operator=(const Simple& simple)
	{
		std::cout << "���� ���� ������ ȣ��" << std::endl;
	}
};

int main()
{
	Simple Sim1(15, 30);

	Simple Sim2 = Sim1;

}