#include <iostream>
#include <algorithm>
#include <complex>

struct S
{
	static int a[];
	inline static int n = 1;
	const static int t = 1;
	const static int k;
	const static int m{ 2 };
	constexpr static int arr[] = { 1,2,3 };
	constexpr static std::complex<double> c = { 1,2 }; // 각각 실수와 허수로 들어간다.
};

// 아래는 위의 구조체 내 멤버 변수에 대한 정의문이다.
int S::a[10];
const int S::k = 3;

int main()
{
	S s;
	std::cout << s.m << std::endl;

	for (int i = 0; i < 10; ++i)
	{
		std::cout << s.a[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		std::cout << S::a[i] << " ";
	}
}