#include <iostream>
#include <vector>
#include <deque>
#include <list>

// 아래는 콘솔에 출력을 위한 << 비트 이동 연산자 오버로딩이다. 참고로 연산자 오버로딩은 암시적인
// 템플릿 변환만이 가능하다.
template<template<class, class...> class C, typename T, class... Args>
std::ostream& operator<<(std::ostream& os, const C<T, Args...>& objs)
{
	for (auto const& obj : objs)
	{
		os << obj << " ";
	}
	return os;
}

// deque 클래스 template<class T, class Allocator = std::allocator<T>> class deque 로 선언되어 있다.
// 따라서 V 템플릿 템플릿 매개변수를 대신하여 deque 클래스 템플릿을 암시적인 방법으로 사용하고 자
// 한다면 2개의 템플릿 매개변수를 선언해주어야 한다.
template<template<class, class> class V, class T, class A>
void f(V<T, A>& v)
{
	for (auto const& Temp : v)
	{
		std::cout << Temp << " ";
	}
	std::cout << std::endl;
}

template<template<class> class v, class T>
void g(v<T>& v)
{
	while (!v.empty())
	{
		T temp = v.back();
		v.pop_back();
		std::cout << temp << " ";
	}
	std::cout << std::endl;
}

int main()
{
	std::vector<double> vf{ 1.1, 2.2, 3.3, 4.4 };
	// 연산자 오버로딩에 대해 명시적 템플릿 변환을 적용하고 자 한다면 에러가 발생한다.
	std::cout << vf << std::endl;

	std::deque<int> di{ 1,2,3,4 };
	f(di);
	std::list<char> lc{ 'a','b','c','d' };
	f<std::list, char>(lc);

	//g(di); //암시적 템플릿 변환을 사용하고 자 한다면 에러가 발생한다.
	g<std::deque, int>(di);
	return 0;
}