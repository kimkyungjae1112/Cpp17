#include <iostream>
#include <future>

int main()
{
	auto F = []()
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "작업 종료" << '\n';
		};

	auto Handle = std::async(F);
	std::cout << "비동기 함수 호출" << std::endl;
	Handle.wait();
	return 0;
}