#include <iostream>
#include <string>

int main()
{
	const char* cc = "���ڿ��� �Է��մϴ�. This is a string";
	std::string str; // string Ÿ������ ������ �����Ѵ�.

	str = cc; // char Ÿ���� ���ڿ��� �����ϴ��� ����� �����ϴ�.
	std::cout << "str = " << str.data() << ", ���ڿ��� ũ��� " << str.length() << std::endl;

	str = "Ŭ���� ���ο��� ������ ��´�.";
	// ����ó�� ���굵 �����ϴ�. �Ʒ��� ���ڿ��� �̾ ���� ����̴�.
	str += " ���� ���� �޸� ������ ���� �ʾƵ� ����� �����ϴ�.";
	std::cout << "str = " << str.data() << ", ���ڿ��� ũ��� " << str.length() << std::endl;
	return 0;
}

/*

��� ���

str = ���ڿ��� �Է��մϴ�. This is a string, ���ڿ��� ũ��� 37
str = Ŭ���� ���ο��� ������ ��´�. ���� ���� �޸� ������ ���� �ʾƵ� ����� �����ϴ�., ���ڿ��� ũ��� 85

*/