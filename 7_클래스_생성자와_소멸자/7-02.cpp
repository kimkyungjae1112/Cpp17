#include <iostream>
#include <cstdio>

class Complex
{
public:
	Complex(int x) : real(x), imaginary(0.0)
	{
		std::cout << "Complex(int x) 호출" << std::endl;
	}

	Complex(double x, double y) : real(x), imaginary(y)
	{
		std::cout << "Complex(double x, double y) 호출" << std::endl;
	}

private:
	double real;
	double imaginary;
};

int main()
{
	// 1. Ok : 숫자를 인수르 인식하여 Complex::Complex(int) 생성자를 호출한다.
	Complex a1 = 1;

	// 2. Ok : 직접 Complex::Complex(int) 생성자를 호출한다.
	Complex a2(2);

	// 3. Ok : 직접 Complex::Complex(double, double) 생성자를 호출한다.
	Complex a3{ 4,5 };

	// 4. Ok : 숫자를 인수로 만들어 Complex::Complex(double, double) 생성자를 호출한다.
	Complex a4 = { 4,5 };

	// 5. Ok : 아래 변환 작업은 Complex::Complex(int) 생성자를 호출한다.
	Complex a5 = (Complex)1;
	
	Complex* a6 = new Complex(4, 5);
	delete a6;
}