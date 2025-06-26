//��� ǥ������ ������ inline �Լ�ó�� ����Ѵ�.
#include <iostream>
using namespace std;

constexpr unsigned long fibonacci(unsigned long i)
{
	return (i <= 1ul) ? i : (fibonacci(i - 1) + fibonacci(i - 2));
}

int main()
{
	// �Ʒ� ������ 'unsigned long l = 610;'�� �����ϰ� ó���ȴ�.
	// �Լ��� �μ��� ����� �Է��ϱ� ������ ������ ������ ����� �νĵȴ�.
	unsigned long i = fibonacci(15);
	cout << i << " = fibonacci(15)" << endl;

	constexpr int z = fibonacci(15);
	cout << z << " : z�� ��" << endl;
	
	int a;
	cin >> a;
	// ����! constexpr int y = fibonacci(a);

	return 0;
}