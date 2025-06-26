#include <iostream>
#include <future>
#include <vector>

int AccumulateBlockWorkerRet(int* Data, size_t Count)
{
	int Result = 0;
	for (size_t i = 0; i < Count; ++i)
		Result += *(Data + i);
	return Result;
}

int main()
{
	std::vector<int> Vec{ 1,2,3,4,5,6,7,8,9,10 };

	// async로 대체
	std::future<int> Fut = std::async(std::launch::async,
		AccumulateBlockWorkerRet, Vec.data(), Vec.size());

	// future 클래스가 제공하는 get() 함수를 사용한다면 작업 결과를 반환받기 위해
	// async() 함수가 종료될 때까지 대기하게 된다.
	std::cout << "배열의 합은 : " << Fut.get() << std::endl;
	return 0;
}