#include <iostream>
#include <cstring>

int main()
{
	char en[] = "Hello World";
	std::cout << "char " << en << std::endl;

	std::cout << "�Է� ���� : ";
	std::cin >> en;
	for (int i = 0; en[i]; ++i)
	{
		std::cout << (char)en[i];
	}
	std::cout << std::endl;

	char wc1[] = "�ѱ�ȭ �۾�"; //OK
	std::cout << wc1 << std::endl; // ���� �ܼ� ȭ������ ��µ� �����ϴ�.

	// �Ʒ��� ���� �ѹ���Ʈ ������ ���ڸ� ȭ�鿡 ����ϴ��� �����ڵ尡 ��µȴ�.
	int i = 0;
	while (wc1[i])
	{
		std::cout << (char)wc1[i];
		++i;
	}
	std::cout << std::endl;

	const char* wc2 = "�ѱ�ȭ �۾�"; //OK
	std::cout << wc2 << ", ���� ũ�� : " << strlen(wc2) << std::endl;
	return 0;
}