#include <iostream>
#include <future>
#include <thread>

int main()
{
	// 1. async() 함수로 부터 future 객체를 얻는다.
	std::future<int> F1 = std::async(std::launch::async, []() { return 1; });

	// 2. promise 객체를 생성하고 future 객체를 얻는다.
	std::promise<int> P;
	std::future<int> F2 = P.get_future();
	std::thread([](std::promise<int>&& P) { P.set_value(2); }, std::move(P)).detach();

	// 3. packaged_task 객체를 생성하고 future 객체를 얻는다.
	std::packaged_task<int()> Task([]() { return 3; });
	std::future<int> F3 = Task.get_future();
	std::thread(std::move(Task)).detach();

	std::cout << "Waiting...\n";
	F1.wait();
	F2.wait();
	F3.wait();
	std::cout << "작업 결과 : " << F1.get() << ' ' << F2.get() << ' ' << F3.get() << '\n';
}