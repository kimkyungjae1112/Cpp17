#include <iostream>

struct S2
{
	void Func(int i);
	int a;
};

void S2::Func(int i)
{
	[&] {}; // Ok : i �Ű� ������ ���� ���� ĸó(ĸó ����Ʈ)
	[=] {}; // Ok : i �Ű� ������ ���� �� ĸó(ĸó ����Ʈ)
	[&, i] {}; // Ok : i ������ �����ϰ� ������ ������ ���� ĸó ���
	[=, &i] {}; // Ok : i ������ ���� ĸó�� ���ǰ� ������ ��δ� �� ĸó�� ���
	//[&, &i] {}; Error : ������ ����ϴ� �� �ߺ�

	// [=, this] { this->a = i; }; //C++ 20 ���� this ĸó�� �����ѵ�?
}

int main()
{
	int m = 0;
	int n = 0;

	// ���� ���� �Լ��� �����ϴ� ���ÿ� () �Լ� ȣ�� �����ڸ� ����Ͽ� �����Ų��.
	[&, n](int a) mutable { m = (++n) + a; }(4);

	// n�� �� �μ�(pass by value)�� ���� ���ο��� �����Ǵ��� ��ȭ���� �ʴ´�.
	// ������ ���� ĸó�� ���� ����
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
		// 'lambda' : �Լ��� ���ܸ� Throw ���� �ʵ��� �����Ǿ� �־� ������ �߻��Ѵ�.
		[]() throw() { throw 5; }();
	}
	catch (int e)
	{
		std::cout << e << '\n';
	}
}