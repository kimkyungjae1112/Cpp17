#include <iostream>

// �� ���� �μ� ��� �ּ� ���� ��ȯ�Ѵ�.
template<typename T>
T Min(T a, T b)
{
	return (a < b) ? a : b;
}

// class �� Type �� ����
template<class Type>
Type Max(Type a, Type b)
{
	return (a > b) ? a : b;
}

int main()
{
	// �����Ϸ��� �μ��� ���� �Ͻ������� Max<int>�� �ν� 
	std::cout << "Max : " << Max(5, 6) << std::endl;

	std::cout << "Min : " << Min(5, 6) << std::endl;

	// �����
	std::cout << "Max : " << Max<double>(5.3, 5.0) << std::endl;
}