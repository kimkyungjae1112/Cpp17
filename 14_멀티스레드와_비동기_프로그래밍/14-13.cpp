#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <vector>

void Accumulate_Block_Worker(int* Data, size_t Count, int* Result)
{
	for (size_t i = 0; i < Count; ++i)
	{
		*Result += *(Data + i);
	}
}

int main()
{
	std::vector<int> Vec{ 1,2,3,4,5,6,7,8,9,10 };
	int Result = 0;

	// vector 클래스에서 제공하는 T* data() 함수는 벡터 객체의 요소를 T[]와 같은 배열로
	// 만들어 반환하는 기능을 제공한다.
	std::thread Worker(Accumulate_Block_Worker, Vec.data(), Vec.size(), &Result);
	Worker.join();
	std::cout << "배열의 합은 : " << Result << '\n';
	return 0;
}