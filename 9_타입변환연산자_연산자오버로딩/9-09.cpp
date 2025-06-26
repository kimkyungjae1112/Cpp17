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

	// 1. ���� ������ �����ε�
	Complex& operator+();
	Complex operator-();

	// ���� ������ �����ε��� ��ȯ�ϴ� ��ü�� *this�� ���� �����̴�. �ݸ鿡 ���� ���� �����ڴ� �Լ�
	// ���ο��� �ӽ� ��ü�� �����Ͽ� ��ȯ�Ѵ�. �ӽ� ��ü�� '���� �̵� ������ ��Ģ'�� ����
	// �Ϲ� ��ü�� �����ȴ�.
	Complex& operator++();		// ++ ���� ������ �����ε�
	Complex operator++(int);	// ++ ���� ������ �����ε�
	Complex& operator--();		// -- ���� ������ �����ε�
	Complex operator--(int);	// -- ���� ������ �����ε�


	// 2. ���� ��� ������ �����ε�
	// �Ʒ� ���� ��� �������� �۾� ����� rvalue �̴�. ���� ���� �۾� ����� �ӽ� ��ü�� �����
	// ��ȯ�Ѵ�. ���� ���� ������ �����ε��� �Ʒ��� ���� inline(�Ǵ� ��� ǥ����)���� ������
	// �����ϸ�, ���� ���� ������ �����ε����� ���� ����.
	// inline constexpr Complex operator+(const Complex& lhs) const;
	Complex operator+(const Complex& c) const;
	Complex operator-(const Complex& c) const;
	Complex operator*(const Complex& c) const;
	Complex operator/(const Complex& c) const;
	
	// ���� ������ �۾� ����� ��ü ��ü�� ��ȭ�� �߻���Ű�Ƿ� ������ ���� ������ ����Ѵ�.
	// ���⼭�� ���� ���� �����ڸ� �����Ͽ���.
	Complex& operator=(const Complex& c);
	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);

	// ���� �� ������ �����ε�(�ʿ��ϴٸ� ���� ������ �����ε����� ���� ����)
	bool operator==(const Complex& c);
	bool operator!=(const Complex& c);


	// 3. Ÿ�� ��ȯ ������ �����ε� (Complex -> double �Ǵ� Complex -> char)
	//    �ڱ� �ڽ��� ��ü�� ���� �Ǵ� �Ǽ��� ����� �ش�.
	operator double();

	// 'std<<cout << Complex(x, y)' ó�� ���Ҽ��� ����ϱ� ���� �����ε��� ���־�� �Ѵ�.
	friend std::ostream& operator<<(std::ostream& os, const Complex& c);

	// ������ �����͸� ��ȯ�Ѵ�.
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

// - ���� �������� �۾� ����� rvalue(�ӽ� ��ü)�� ����� ��ȯ�Ѵ�.
// �׸��� RVO ����/�̵� ������ ��Ģ�� ���� ��ü�� �ȴ�.
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