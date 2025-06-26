#include <iostream>

template<typename T>
void print(const T& t)
{
	std::cout << t << std::endl;
}

// 첫 번째 인수는 일반 타입 매개변수를 만들고 두 번째 인수는 가변 매개변수로 만든다.
template<typename First, typename... Rest>
void print(const First& first, const Rest&... rest)
{
	std::cout << first << ", ";
	print(rest...); // 함수의 나머지 인수에 대해 함수를 반복 호출시킨다.
}

template<typename... Ts>
void func(Ts... args)
{
	// sizeof... 는 가변 인수의 개수를 변환한다.
	const int size = sizeof...(args) + 2;

	// 가변 인수를 배열로 만든다.
	int res[size] = { 1, args..., 2 };
	std::cout << "size of " << size << std::endl;

	// 범위 기반 for 문 내부에 가변 인수를 사용할 수 있다.
	for (auto i : { args... }) { std::cout << i << " "; }
	std::cout << std::endl;

	// 람다 내 캡처절 또는 인수로 만들어 사용할 수 있다.
	auto lm = [&, args...] { return print(args...); }
	lm();

}

int main()
{
	print(1);
	print(10, 20);
	print(100, 200, 300);
	print("First", 2, "Third", 3.115, 15);
}