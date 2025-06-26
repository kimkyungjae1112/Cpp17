#include <iostream>

int main()
{
	int a = 1, b = 1, c = 1;

	// 람다의 캡처절은 위의 변수들을 받아들인다.
	auto m1 = [a, &b, &c]() mutable
		{
			a = 3; b = 3; c = 3;
		};

	a = 2; b = 2; c = 2;

	// 람다를 선언하는 동시에 정의한다.
	auto m2 = [=]() mutable
		{
			a = 4; b = 4; c = 4;
		};

	m1();
	std::cout << a << ' ' << b << ' ' << c << '\n'; // 2 3 3 출력
}