#include <iostream>

int main()
{
	int a = 1, b = 1, c = 1;

	// ������ ĸó���� ���� �������� �޾Ƶ��δ�.
	auto m1 = [a, &b, &c]() mutable
		{
			a = 3; b = 3; c = 3;
		};

	a = 2; b = 2; c = 2;

	// ���ٸ� �����ϴ� ���ÿ� �����Ѵ�.
	auto m2 = [=]() mutable
		{
			a = 4; b = 4; c = 4;
		};

	m1();
	std::cout << a << ' ' << b << ' ' << c << '\n'; // 2 3 3 ���
}