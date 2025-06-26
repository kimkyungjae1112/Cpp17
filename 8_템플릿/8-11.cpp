#include <iostream>

template<class T>
T Min(T a, T b)
{
	return (a < b) ? a : b;
}

int main()
{
	int tmp01 = 10;
	int tmp02 = 20;
	int* a = &tmp01, *b = &tmp02;

	std::cout << "1. �ּڰ� : " << Min(*a, *b) << std::endl;
	std::cout << "2. �ּڰ� : " << Min<int*>(a, b) << std::endl;
}