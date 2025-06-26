#include <iostream>
#include <iomanip>
#include <locale>

//일자를 'xx/xx/xxxx' 포맷으로 콘솔 화면에 출력한다.
void ShowData(int m, int d, int y)
{
	// 1. 아래 문자은 문자 폭을 채울 수 없다면, '0'으로 채우라는 의미로 사용한다.
	std::cout << std::setfill('0');

	// 2. setw(2)는 데이터의 폭을 두 문자를 채울 수 있는 크기로 하라는 의미이다.
	//	  setw(4)는 데이터의 폭을 네 문자를 채울 수 있는 크기로 하라는 의미이다.
	std::cout << std::setw(2) << m << '/'
		<< std::setw(2) << d << '/'
		<< std::setw(4) << y << std::endl;
	std::cout << std::endl;
}

int main()
{
	// 원주율을 std::defaultfloat 타입으로 출력한다.
	// std::defaultfloat 타입은 소숫점 이하 6자리를 반올림하여 5자리로 출력한다.
	double f = 3.1415926535;
	std::cout << f << std::endl;

	double x = 800000.0 / 81.0;
	// 3. std::fixed는 실수를 출력할 때 고정 소숫점 자리를 사용한다.
	// 4. std::setprecision(2)은 소숫점이하 자리를 2로 한다는 의미로 사용한다.
	std::cout << std::fixed << std::setprecision(2) << x << std::endl;
	x = 2.0 / 3.0;

	// std::setprecision(4)은 소숫점 이하 자리를 4로 한다는 의미로 사용한다.
	std::cout << std::fixed << std::setprecision(4) << x << std::endl;
	std::cout << std::endl;

	// 위의 일자 함수를 호출한다.
	ShowData(1, 1, 2019);

	unsigned long x0 = 64206;
	// 5. 아래 std::showbace는 숫자를 출력할 때 진법을 표시하라는 의미로 사용한다.
	//	8진법은 '0'으로 16진법은 '0x'로 표시한다. 사용하지 않을 때 'std::noshowbase'를 사용한다.
	//	std::oct는 8진법으로 숫자를 표시한다. std::hex는 16진법으로 숫자를 표시한다.
	std::cout << x0 << std::showbase
		<< " 8진법은 \"" << std::oct << x0 << "\""
		<< " 16진법은 \"" << std::hex << x0 << "\"" << std::endl;
	std::cout << std::endl;
	return 0;
}