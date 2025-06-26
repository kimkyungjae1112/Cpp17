#include <iostream>
#include <string>

using namespace std;

class Shape
{
public:
	Shape(string sName) : sName(sName) {}

	void Area() { cout << "도형 이름 : " << GetName() << ", 넓이 : " << GetArea(); }
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

int main()
{
	Shape* Sp[] = {
		new Rectangle("직사각형", 10, 5),
		new Triangle(10, 5),
		new Circle(10)
	};

	for (Shape* S : Sp)
	{
		S->Area();
		std::cout << std::endl;
	}

	for (Shape* S : Sp)
	{
		delete S;
	}

	return 0;
}