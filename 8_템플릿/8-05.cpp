#include <iostream>

// Ÿ���� �ƴ� ���ø� �Ű������� ������ ����Ѵ�.
template<int& ri>
struct Simple
{
	/*Simple()
	{
		printf("��ü ���� �� ri�� %d �̴�.\n", ri);
	}
	~Simple()
	{
		printf("��ü �Ҹ� �� ri�� %d �̴�.\n", ri);
	}*/
};

int i = 1;

int main()
{
	// �ݵ�� ���� ������ ����Ͽ� ��ü�� �����ؾ� �Ѵ�. ���� ���� ������ ����Ѵٸ�, ������ ������
	// �����͸� Ȯ������ ���� ������ �߻��Ѵ�.
	Simple<i> S;
	i = 0;
	return 0;
}