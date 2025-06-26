#include <iostream>

class Complex
{
public:
	constexpr Complex(double r, double i) : dRealValue(r), dImaginary(i) {}
	constexpr double GetReal() const { return dRealValue; }
	constexpr double GetImag() const { return dImaginary; }

private:
	double dRealValue;
	double dImaginary;
};

constexpr Complex Comp(0.0, 1.0);

int main()
{
	double x = 1.0;

	// 1. 생성자의 인수로 리터럴을 사용하였으므로 사용이 가능하다.
	constexpr Complex Cx1(1.0, 0.9);

	// 2. constexpr 지정자로 선언한 인수는 상수가 되어야 한다. 따라서 생성자의 인수로
	//    변수를 사용한다면 x 변수의 값을 알 수 있다하더라도 에러가 발생한다.
	// constexpr Complex Cx1(x, 1);

	// 3. 다음 Cx2 변수는 constexpr 지정자로 선언된 상수가 아니기 때문에 허용된다.
	const Complex Cx2(x, 1); // Ok

	// 4. Comp 변수는 constexpr 지정자로 선언되어 있으므로 내부 변수 역시 모두
	//    상수이므로 다음과 같이 상수를 초기화하는 데 허용된다.
	constexpr double XX = Comp.GetReal(); // Ok
	constexpr double ImagVal = Comp.GetImag(); // Ok
	double xd = Comp.GetReal(); // Ok

	// 5. 상수표현식으로 선언된 생성자는 리터럴로 인식되므로 일반 변수를 생성하는 데
	//    사용하더라도 전혀 문제가 되지 않는다.
	Complex Cx3(2.0, 4.6);
	
	// int a;
	// Complex Cx4(a, 4.0); 에러!

	return 0;
}