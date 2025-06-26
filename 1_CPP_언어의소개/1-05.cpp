#pragma warning(disable: 4996) // ���־� ��Ʃ��� ��� �� �߰��Ѵ�.
#include <cstring>
#include <cstdlib>
#include <iostream>

int main()
{
	const char* cc = "���ڿ��� �Է��մϴ�. This is a string";
	char cb[17]; // ���ڿ��� ���� �� 16�� ���ڿ� ������ ���ڷ� NULL�� ����Ѵ�.
	char* str; // ���ڿ� �����ʹ�.

	memcpy(cb, cc, 17); // ���� 'strcpy(cb, cc);'�� ����Ѵٸ� ������ �߻��Ѵ�.
	str = (char*)malloc(strlen(cc) + 1); // ���ڿ��� �����ϱ� ���� �޸� ������ �Ҵ�޴´�.
	strcpy(str, cc);

	// �Ʒ��� ���� '\0'�� ���� ������ ������ ũ�⸦ �Ѿ� �Ϻ� �����Ͱ� ������ ������ �߻��Ѵ�.
	std::cout << "cc = " << cc << ", ���ڿ��� ũ��� " << strlen(cc) << std::endl;
	std::cout << "cb = " << cb << ", ���ڿ��� ũ��� " << strlen(cb) << std::endl;
	std::cout << "str = " << str << ", ���ڿ��� ũ��� " << strlen(str) << std::endl;
	free(str);
}


/* 

��°��

cc = ���ڿ��� �Է��մϴ�. This is a string, ���ڿ��� ũ��� 37
cb = ���ڿ��� �Է��մ�������������������������������?2��?, ���ڿ��� ũ��� 54
str = ���ڿ��� �Է��մϴ�. This is a string, ���ڿ��� ũ��� 37

*/