#include <iostream>

struct Simple
{
	// ��ü�� �����ϱ� ���� �޸� ������ Ȯ���ϴ� new ������ �����ε��̴�.
	// new ������ �����ε��� ��ü ���� ������ ȣ��Ǵ� �������̹Ƿ� static ����
	// �������־�� �Ѵ�.

	static void* operator new(std::size_t sz)
	{
		std::cout << "new called.\n";

		// ���� ���ӽ����̽� �� �����ϴ� new �����ڸ� ȣ���Ѵ�.
		return ::operator new(sz);
	}

	// Ȯ���� �޸� ������ �ü���� ��ȯ�ϴ� delete ������ �����ε��̴�.
	static void operator delete(void* ptr)
	{
		std::cout << "delete called.\n";

		::operator delete(ptr);
	}
};

int main()
{
	Simple* simple = new Simple;

	delete simple;
}