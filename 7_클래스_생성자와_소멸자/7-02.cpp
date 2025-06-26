#include <iostream>
#include <cstdio>

class Complex
{
public:
	Complex(int x) : real(x), imaginary(0.0)
	{
		std::cout << "Complex(int x) ȣ��" << std::endl;
	}

	Complex(double x, double y) : real(x), imaginary(y)
	{
		std::cout << "Complex(double x, double y) ȣ��" << std::endl;
	}

private:
	double real;
	double imaginary;
};

int main()
{
	// 1. Ok : ���ڸ� �μ��� �ν��Ͽ� Complex::Complex(int) �����ڸ� ȣ���Ѵ�.
	Complex a1 = 1;

	// 2. Ok : ���� Complex::Complex(int) �����ڸ� ȣ���Ѵ�.
	Complex a2(2);

	// 3. Ok : ���� Complex::Complex(double, double) �����ڸ� ȣ���Ѵ�.
	Complex a3{ 4,5 };

	// 4. Ok : ���ڸ� �μ��� ����� Complex::Complex(double, double) �����ڸ� ȣ���Ѵ�.
	Complex a4 = { 4,5 };

	// 5. Ok : �Ʒ� ��ȯ �۾��� Complex::Complex(int) �����ڸ� ȣ���Ѵ�.
	Complex a5 = (Complex)1;
	
	Complex* a6 = new Complex(4, 5);
	delete a6;
}