#include <iostream>

struct S2
{
	void Func(int i);
	int a;
};

void S2::Func(int i)
{
	[&] {}; // Ok : i 매개 변수에 대해 참조 캡처(캡처 디폴트)
	[=] {}; // Ok : i 매개 변수에 대해 값 캡처(캡처 디폴트)
	[&, i] {}; // Ok : i 변수를 제외하고 나머지 변수는 참조 캡처 사용
	[=, &i] {}; // Ok : i 변수는 참조 캡처로 사용되고 나머지 모두는 값 캡처로 사용
	//[&, &i] {}; Error : 참조로 사용하는 것 중복

	// [=, this] { this->a = i; }; //C++ 20 부터 this 캡처가 가능한데?
}

int main()
{
	int m = 0;
	int n = 0;

	// 무명 람다 함수를 생성하는 동시에 () 함수 호출 연산자를 사용하여 실행시킨다.
	[&, n](int a) mutable { m = (++n) + a; }(4);

	// n은 값 인수(pass by value)로 람다 내부에서 수정되더라도 변화되지 않는다.
	// 참조로 받은 캡처는 수정 가능
	std::cout << m << ' ' << n << std::endl;

	int a = 1, b = 1, c = 1;
	[a, &b, &c]() mutable { a = 3; b = 3; c = 3; }();

	std::cout << a << " " << b << " " << c << std::endl;

	auto ID = [](int n) constexpr { return n; };
	constexpr int I = ID(3);

	auto f = [](int x) throw() -> bool { return x % 3 == 0; };
	auto h = []() throw() { return rand(); };
	std::cout << f(2) << " " << h() << '\n';
	
	try
	{
		// 'lambda' : 함수는 예외를 Throw 하지 않도록 지정되어 있어 에러가 발생한다.
		[]() throw() { throw 5; }();
	}
	catch (int e)
	{
		std::cout << e << '\n';
	}
}