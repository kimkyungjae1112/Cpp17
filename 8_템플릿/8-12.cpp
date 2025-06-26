#include <iostream>
#include <type_traits>
#include <string>

using namespace std;

// ���ø� �μ��� lvalue ������ �ƴ϶��, �Ʒ� �Լ� ���ø��� Ȱ��ȭ��Ų��.
template<class T>
typename std::enable_if<!std::is_lvalue_reference<T>::value, T&>::type min(T& a, T& b)
{
	std::cout << "�� ��";
	return (a < b) ? a : b;
}

// ���ø� �μ��� lvalue �����̶�� �Ʒ� �Լ� ���ø��� Ȱ��ȭ��Ų��.
template<class T>
typename std::enable_if<std::is_lvalue_reference<T>::value, T>::type min(T a, T b)
{
	std::cout << "�� ��";
	return (a < b) ? a : b;
}

// ���ø� �μ��� �����Ͷ�� �Ʒ� �Լ� ���ø��� Ȱ��ȭ��Ų��.
template<class T>
T min(T* a, T* b)
{
	std::cout << "������";
	return (*a < *b) ? *a : *b;
}


class Shape
{
public:
	Shape(string sName) : sName(sName) {}

	void Area() { cout << "���� �̸� : " << GetName() << ", ���� : " << GetArea(); }
	virtual double GetArea() { return 0; }

	const string& GetName() { return sName; }

private:
	string sName;
};

class Rectangle : public Shape
{
public:
	Rectangle(string sName, float fWidth = 0, float fHeight = 0) : Shape(sName), fWidth(fWidth), fHeight(fHeight) {}

	virtual double GetArea() override { return fWidth * fHeight; }

private:
	float fWidth;
	float fHeight;
};

class Triangle : public Rectangle
{
public:
	Triangle(float fWidth = 0, float fHeight = 0) : Rectangle("Triangle", fWidth, fHeight) {}

	virtual double GetArea() final override { return (Rectangle::GetArea()) / 2.f; }

};

const double PI = 3.141592;
class Circle : public Shape
{
public:
	Circle(double dRadius = 0) : Shape("Circle"), dRadius(dRadius) {}

	virtual double GetArea() override { return PI * dRadius * dRadius; }

private:
	double dRadius;
};

bool operator<(Shape& a, Shape& b)
{
	return a.GetArea() < b.GetArea();
}

bool operator>(Shape& a, Shape& b)
{
	return a.GetArea() > b.GetArea();
}

int main()
{
	int tmp01 = 10;
	int tmp02 = 20;
	int& tmp03 = tmp01;
	int& tmp04 = tmp02;
	int* a = &tmp01, *b = &tmp02;
	std::cout << "1. �ּڰ� : " << min<int>(*a, *b) << std::endl;
//	std::cout << "2. �ּڰ� : " << min<int&>(tmp03, tmp04) << std::endl;
	std::cout << "3. �ּڰ� : " << min(a, b) << std::endl;

	Rectangle shape01 = Rectangle("���簢��", 10, 5);
	Circle shape02 = Circle(10);
	std::cout << "4. �ּڰ� : ";
	//Shape& s1 = min<Shape&>(shape01, shape02);
	//s1.GetArea();

	std::cout << "5. �ּڰ� : ";
	Shape& s2 = min<Shape>(shape01, shape02);
	s2.GetArea();

	return 0;
}