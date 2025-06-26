#include <iostream>

template<typename T>
void print(const T& t)
{
	std::cout << t << std::endl;
}

// ù ��° �μ��� �Ϲ� Ÿ�� �Ű������� ����� �� ��° �μ��� ���� �Ű������� �����.
template<typename First, typename... Rest>
void print(const First& first, const Rest&... rest)
{
	std::cout << first << ", ";
	print(rest...); // �Լ��� ������ �μ��� ���� �Լ��� �ݺ� ȣ���Ų��.
}

template<typename... Ts>
void func(Ts... args)
{
	// sizeof... �� ���� �μ��� ������ ��ȯ�Ѵ�.
	const int size = sizeof...(args) + 2;

	// ���� �μ��� �迭�� �����.
	int res[size] = { 1, args..., 2 };
	std::cout << "size of " << size << std::endl;

	// ���� ��� for �� ���ο� ���� �μ��� ����� �� �ִ�.
	for (auto i : { args... }) { std::cout << i << " "; }
	std::cout << std::endl;

	// ���� �� ĸó�� �Ǵ� �μ��� ����� ����� �� �ִ�.
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