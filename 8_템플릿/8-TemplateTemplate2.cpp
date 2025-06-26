#include <iostream>
#include <vector>
#include <deque>
#include <list>

// �Ʒ��� �ֿܼ� ����� ���� << ��Ʈ �̵� ������ �����ε��̴�. ����� ������ �����ε��� �Ͻ�����
// ���ø� ��ȯ���� �����ϴ�.
template<template<class, class...> class C, typename T, class... Args>
std::ostream& operator<<(std::ostream& os, const C<T, Args...>& objs)
{
	for (auto const& obj : objs)
	{
		os << obj << " ";
	}
	return os;
}

// deque Ŭ���� template<class T, class Allocator = std::allocator<T>> class deque �� ����Ǿ� �ִ�.
// ���� V ���ø� ���ø� �Ű������� ����Ͽ� deque Ŭ���� ���ø��� �Ͻ����� ������� ����ϰ� ��
// �Ѵٸ� 2���� ���ø� �Ű������� �������־�� �Ѵ�.
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
	// ������ �����ε��� ���� ����� ���ø� ��ȯ�� �����ϰ� �� �Ѵٸ� ������ �߻��Ѵ�.
	std::cout << vf << std::endl;

	std::deque<int> di{ 1,2,3,4 };
	f(di);
	std::list<char> lc{ 'a','b','c','d' };
	f<std::list, char>(lc);

	//g(di); //�Ͻ��� ���ø� ��ȯ�� ����ϰ� �� �Ѵٸ� ������ �߻��Ѵ�.
	g<std::deque, int>(di);
	return 0;
}