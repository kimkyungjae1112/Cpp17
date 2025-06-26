#include <iostream>
#include <vector>
#include <thread>

using Chrono = std::chrono::steady_clock;
using int_futures = std::vector<std::thread>;

int main()
{
	// 람다를 만들어 인수로 받은 값만큼 작업을 대기 시킨다.
	auto Sleep = [](int s)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(s));
			return s;
		};

	int_futures Futures;
	Chrono::time_point Start = Chrono::now();
	// 하나의 스레드의 작업이 완료되면 다음 스레드가 작업을 수행한다.
	for (int i = 0; i < 10000; ++i)
	{
		Futures.push_back(std::thread(Sleep, 100));
	}

	for (int i = 0; i < 10000; ++i)
	{
		if ((i % 100) == 0)
		{
			std::cout << '.';
		}
		Futures[i].join();
	}
	std::cout << '\n';

	Chrono::time_point End = Chrono::now();
	std::chrono::milliseconds Sec =
		std::chrono::duration_cast<std::chrono::milliseconds>(End - Start);
	std::cout << "실행 시간 : " << Sec.count() << " 밀리초" << std::endl;
}