#include <iostream>

void Test()
{
	static int var;
	++var;

	std::cout << var << std::endl;
}

int main()
{
	Test();
	Test();
	//int a = var; ���� �߻�

	return 0;
}

// �Լ� ���ο� ����� ���� ������ ��ġ �Լ� �ܺο� ����� ���� ����ó�� ���ȴ�.
// ������ �Լ� ���ο� ������ ���� ������ ���� ����ó�� ����ϴ��� �Լ� �ܺο��� ȣ��� �� ����.