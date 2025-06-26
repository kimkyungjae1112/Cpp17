#include <cstdlib>
#include <iostream>

int main()
{
	int array[10];
	for (int i = 0; i < 10; ++i)
	{
		array[i] = std::rand() % 1000;
	}

	std::cout << "sort �� : ";
	for (int i = 0; i < 10; ++i)
	{
		std::cout << array[i] << " ";
	} 
	std::cout << std::endl;


	// �Ʒ� ���ٴ� ���Ŀ� ���� �� �Լ��� ����Ѵ�. 
	// ������ Ÿ�� ���
	// �μ��� �Լ�ó�� �����͸� ���ٿ� ������ �� ���ȴ�.
	auto sorter = [](const void* first, const void* second) -> int
		{
			return (*(int*)first - *(int*)second);
		};

	qsort(array, 10, sizeof(int), sorter);
	
}