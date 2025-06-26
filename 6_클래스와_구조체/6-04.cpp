#include <iostream>

using std::cout;
using std::endl;

class Something
{
private:
	static int iValue;			// ���� ��� �����̴�.
	static const int ciValue;   // ���� ��� ����̴�.

public:
	// ���� �Լ��� ������ ���� ��� ������ ���� ��� ��� �׸���
	// ���� �Լ����� ȣ���� �� �ִ�.
	// ���� �Լ��� ��ü�� �������� �ʴ��� ȣ���� �����ϹǷ� �ʱ�ȭ �Ǿ� ���� ����
	// �Ϲ� ��� ������ �Լ��� ����� �� ����.
	static int GetValue() { return iValue; }
	static const int GetConst() { return ciValue; }
};

int Something::iValue = 1; // ���� ��� ������ �ʱ�ȭ�Ѵ�.
const int Something::ciValue = 10; // ���� ��� ��� ������ �ʱ�ȭ�Ѵ�.

int main()
{
	cout << "Something::GetValue() = " << Something::GetValue() << endl;
	cout << "Something::GetConst() = " << Something::GetConst() << endl;
}