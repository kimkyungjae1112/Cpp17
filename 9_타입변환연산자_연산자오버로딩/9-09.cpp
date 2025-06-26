#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <cmath>

struct Complex
{
public:
	constexpr Complex(double dReal);
	constexpr Complex(double dReal, double dImaginary);

	// 1. 단항 연산자 오버로딩
	Complex& operator+();
	Complex operator-();

	// 전위 연산자 오버로딩이 반환하는 객체는 *this에 대한 참조이다. 반면에 후위 단항 연산자는 함수
	// 내부에서 임시 객체를 생성하여 반환한다. 임시 객체는 '복사 이동 생략의 원칙'에 따라
	// 일반 객체로 변형된다.
	Complex& operator++();		// ++ 전위 연산자 오버로딩
	Complex operator++(int);	// ++ 후위 연산자 오버로딩
	Complex& operator--();		// -- 전위 연산자 오버로딩
	Complex operator--(int);	// -- 후위 연산자 오버로딩


	// 2. 이항 산술 연산자 오버로딩
	// 아래 이항 산술 연산자의 작업 결과는 rvalue 이다. 따라서 연산 작업 결과는 임시 객체를 만들어
	// 반환한다. 또한 이항 연산자 오버로딩은 아래와 같이 inline(또는 상수 표현식)으로 선언이
	// 가능하며, 또한 전역 연산자 오버로딩으로 만들어도 좋다.
	// inline constexpr Complex operator+(const Complex& lhs) const;
	Complex operator+(const Complex& c) const;
	Complex operator-(const Complex& c) const;
	Complex operator*(const Complex& c) const;
	Complex operator/(const Complex& c) const;
	
	// 대입 연산자 작업 결과는 자체 객체의 변화를 발생시키므로 다음과 같이 참조를 사용한다.
	// 여기서는 복사 대입 연산자만 선언하였다.
	Complex& operator=(const Complex& c);
	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);

	// 이항 비교 연산자 오버로딩(필요하다면 전역 연산자 오버로딩으로 만들어도 좋다)
	bool operator==(const Complex& c);
	bool operator!=(const Complex& c);


	// 3. 타입 변환 연산자 오버로딩 (Complex -> double 또는 Complex -> char)
	//    자기 자신의 객체를 정수 또는 실수로 만들어 준다.
	operator double();

	// 'std<<cout << Complex(x, y)' 처럼 복소수를 출력하기 위해 오버로딩을 해주어야 한다.
	friend std::ostream& operator<<(std::ostream& os, const Complex& c);

	// 변수의 데이터를 반환한다.
	inline double GetReal() const { return dReal; }
	inline double GetImaginary() const { return dImaginary; }

private:
	double dReal;
	double dImaginary;
};

constexpr Complex::Complex(double dReal) : dReal(dReal), dImaginary(0.0)
{

}

constexpr Complex::Complex(double dReal, double dImaginary) : dReal(dReal), dImaginary(dImaginary)
{

}

Complex& Complex::operator+()
{
	return *this;
}

// - 단항 연산자의 작업 결과는 rvalue(임시 객체)를 만들어 반환한다.
// 그리고 RVO 복사/이동 생략의 원칙에 따라 객체가 된다.
Complex Complex::operator-()
{
	Complex complex(-this->dReal, -this->dImaginary);
	return complex;
}

Complex& Complex::operator++()
{
	++this->dReal;
	++this->dImaginary;
	return *this;
}
Complex Complex::operator++(int)
{
	Complex complex(this->dReal, this->dImaginary);
	++this->dReal;
	++this->dImaginary;
	return complex;
}
Complex& Complex::operator--()
{
	--this->dReal;
	--this->dImaginary;
	return *this;
}
Complex Complex::operator--(int)
{
	Complex complex(this->dReal, this->dImaginary);
	--this->dReal;
	--this->dImaginary;
	return complex;
}

Complex Complex::operator+(const Complex& c) const
{
	return Complex(this->dReal + c.dReal, this->dImaginary + c.dImaginary);
}
Complex Complex::operator-(const Complex& c) const
{
	return Complex(this->dReal - c.dReal, this->dImaginary - c.dImaginary);
}
Complex Complex::operator*(const Complex& c) const
{
	return Complex(
		(this->dReal * c.dReal - this->dImaginary * c.dImaginary),
		(this->dReal * c.dImaginary + this->dImaginary * c.dReal));
}
Complex Complex::operator/(const Complex& c) const
{
	double r = (this->dReal * c.dReal + this->dImaginary * c.dImaginary) /
		((c.dReal * c.dReal) + (c.dImaginary * c.dImaginary));

	double i = (this->dReal * c.dImaginary - this->dImaginary * c.dReal) /
		((c.dReal * c.dReal) + (c.dImaginary * c.dImaginary));

	return Complex(r, i);
}

Complex& Complex::operator=(const Complex& c)
{
	this->dReal = c.dReal;
	this->dImaginary = c.dImaginary;
	return *this;
}
Complex& Complex::operator+=(const Complex& c)
{
	this->dReal += c.dReal;
	this->dImaginary += c.dImaginary;
	return *this;
}
Complex& Complex::operator-=(const Complex& c)
{
	this->dReal -= c.dReal;
	this->dImaginary -= c.dImaginary;
	return *this;
}

bool Complex::operator==(const Complex& c)
{
	return this->dReal == c.dReal && this->dImaginary == c.dImaginary;
}
bool Complex::operator!=(const Complex& c)
{
	return !operator==(c);
}

Complex::operator double()
{
	return this->dReal;
}

std::ostream& operator<<(std::ostream& os, const Complex& c)
{
	os << "( " << c.dReal << " + " << c.dImaginary << "i" << " )";
	return os;
}

int main()
{
	Complex c1(10, 20);
	Complex c2(30, 40);
	std::cout << c1 << c2 << std::endl;
	return 0;
}