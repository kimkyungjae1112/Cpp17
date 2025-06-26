#include <iostream>
#include <numeric>
#include <vector>
#include <future>

int AccumulateBlockWorker(int* Data, size_t Count)
{
	return std::accumulate(Data, Data + Count, 0);
}

using int_futures = std::vector<std::future<int>>;

int_futures LaunchSplitWorkers(std::vector<int>& Vec)
{
	int_futures Futures;
	// 비동기 스레드 객체를 생성하여 벡터 객체에 입력한다.
	size_t Length = Vec.size() / 2;
	Futures.push_back(std::async
		(
			std::launch::async, 
			AccumulateBlockWorker,
			Vec.data(), 
			Length
		)
	);

	Futures.push_back(std::async
		(
			std::launch::async,
			AccumulateBlockWorker,
			Vec.data() + Length,
			Length
		)
	);

	return Futures;
}

int main()
{
	std::vector<int> Vec{ 1,2,3,4,5,6,7,8,9,10 };

	int_futures Futures = LaunchSplitWorkers(Vec);
	// 각각의 작업 결과를 반환받는다.

	int Result0 = Futures[0].get();
	int Result1 = Futures[1].get();
	std::cout << "각 배열의 합은 " << Result0 << " 와 " << Result1 << '\n';
	std::cout << "두 개 배열의 합은 " << Result0 + Result1 << '\n';
	return 0;
}