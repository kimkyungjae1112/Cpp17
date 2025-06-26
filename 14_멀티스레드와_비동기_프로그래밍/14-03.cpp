#include <iostream>
#include <chrono>
#include <thread>

void IndependentThread()
{
	std::cout << "IndependentThread()\n";
	// 함수 작업을 2초간 대기 시킨다.
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "종료 IndependentThread()\n";
}

void Caller()
{
	std::cout << "Caller() 함수 호출. \n";
	std::thread Thread(IndependentThread);
	Thread.detach();
	std::this_thread::sleep_for(std::chrono::seconds(2)); // 2초간 스레드의 작업을 대기시킨다.

	// detach() 함수 또는 join() 함수를 호출하였다면 joinable() 함수는 false 를 반환한다.
	// joinable() 함수는 스레드에 대해 join() 함수를 호출할 수 있는지 확인할 때 사용한다.
	if (Thread.joinable())
	{
		Thread.join();
	}
	std::cout << "Caller() 함수 종료.\n";
}

int main()
{
	std::thread Call(Caller);
	Call.detach();	// 스레드를 분리하여 실행시킨다.
	std::chrono::system_clock::time_point StartTime = std::chrono::system_clock::now();
	std::chrono::seconds Dura_Sec(3);

	// 스레드가 분리된 이후에 메인 스레드가 종료한다면, 일반 스레드 역시 종료된다.
	// 따라서 3초간 대기한다.
	std::this_thread::sleep_until(StartTime + Dura_Sec);
	std::cout << "메인 스레드 종료...\n";
	return 0;
}