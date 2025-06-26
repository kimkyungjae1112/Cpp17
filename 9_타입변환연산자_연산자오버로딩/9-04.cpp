#include <iostream>

int i = 0;

// 1. lvalue 참조를 함수의 매개변수로 사용한다.
void ParamCheck(int& s)
{
	std::cout << ++i << ", " << s << " 인수는 'int&' 타입이다.\n";
}

// 2. lvalue 참조 상수를 함수의 매개변수로 사용한다.
void ParamCheck(const int& s)
{
	std::cout << ++i << ", " << s << " 인수는 'const int&' 타입이다.\n";
}

// 3. rvalue 참조 상수를 함수의 매개변수로 사용한다.
void ParamCheck(int&& s)
{
	std::cout << ++i << ", " << s << " 인수는 'int&&' 타입이다.\n";
}

int main()
{
	int s = 10;
	ParamCheck(s); // 1번째 함수 호출

	const int& cs = s;
	ParamCheck(cs); // 2번째 함수 호출

	// rvalue 참조로 변환한다.
	ParamCheck(static_cast<int&&>(s)); // 3번째 함수 호출

	return 0;
}