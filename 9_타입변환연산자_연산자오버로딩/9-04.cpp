#include <iostream>

int i = 0;

// 1. lvalue ������ �Լ��� �Ű������� ����Ѵ�.
void ParamCheck(int& s)
{
	std::cout << ++i << ", " << s << " �μ��� 'int&' Ÿ���̴�.\n";
}

// 2. lvalue ���� ����� �Լ��� �Ű������� ����Ѵ�.
void ParamCheck(const int& s)
{
	std::cout << ++i << ", " << s << " �μ��� 'const int&' Ÿ���̴�.\n";
}

// 3. rvalue ���� ����� �Լ��� �Ű������� ����Ѵ�.
void ParamCheck(int&& s)
{
	std::cout << ++i << ", " << s << " �μ��� 'int&&' Ÿ���̴�.\n";
}

int main()
{
	int s = 10;
	ParamCheck(s); // 1��° �Լ� ȣ��

	const int& cs = s;
	ParamCheck(cs); // 2��° �Լ� ȣ��

	// rvalue ������ ��ȯ�Ѵ�.
	ParamCheck(static_cast<int&&>(s)); // 3��° �Լ� ȣ��

	return 0;
}