#include <iostream>

// 두 개의 인수 가운데 최소 값을 반환한다.
template<typename T>
T Min(T a, T b)
{
	return (a < b) ? a : b;
}

// class 나 Type 도 가능
template<class Type>
Type Max(Type a, Type b)
{
	return (a > b) ? a : b;
}

int main()
{
	// 컴파일러는 인수를 보고 암시적으로 Max<int>로 인식 
	std::cout << "Max : " << Max(5, 6) << std::endl;

	std::cout << "Min : " << Min(5, 6) << std::endl;

	// 명시적
	std::cout << "Max : " << Max<double>(5.3, 5.0) << std::endl;
}