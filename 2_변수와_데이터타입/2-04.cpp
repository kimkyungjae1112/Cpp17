#include <iostream>

struct Something
{
	static int Svalue; //���� ����� �����ϴ�.
	static int GetSvalue() { return Svalue; } //���� ��� �Լ��� �����Ѵ�.

	int Value; //�Ϲ� ��� ������ �����Ѵ�.
	int GetValue() { return Value; } //�Ϲ� ��� �Լ��� �����Ѵ�.
};

// �Ʒ��� ���� ��� ������ �ʱ�ȭ��ų �� ����ó�� ���� Ȯ�� �����ڸ� ����Ѵ�.
int Something::Svalue = 1;

int main()
{
	// ���� ��� �Լ��� ����ü�� ����� ������ ������ �Ʒ�ó�� ȣ���� �����ϴ�.
	std::cout << Something::GetSvalue() << std::endl;

	// ���� ��� ������ �ƴ� ����ü�� �Ϲ� ��� ������ ���� ����� �Բ� ������ ���� 100���� Value ��� ������ �ʱ�ȭ��ų �� �ִ�.
	Something S = { 100 };

	// ���� ��� �Լ��� �Ϲ� ��� �Լ��� �����ϰ� �Լ��� ȣ���� ������ ����.
	std::cout << S.GetSvalue() << " , " << S.GetValue() << std::endl;
	return 0;
}