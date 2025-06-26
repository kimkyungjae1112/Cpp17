#include <cstdlib>
#include <iostream>

int main()
{
	int array[10];
	for (int i = 0; i < 10; ++i)
	{
		array[i] = std::rand() % 1000;
	}

	std::cout << "sort 전 : ";
	for (int i = 0; i < 10; ++i)
	{
		std::cout << array[i] << " ";
	} 
	std::cout << std::endl;


	// 아래 람다는 정렬에 따른 비교 함수로 사용한다. 
	// 데이터 타입 명시
	// 인수는 함수처럼 포인터를 람다에 전달할 때 사용된다.
	auto sorter = [](const void* first, const void* second) -> int
		{
			return (*(int*)first - *(int*)second);
		};

	qsort(array, 10, sizeof(int), sorter);
	
}