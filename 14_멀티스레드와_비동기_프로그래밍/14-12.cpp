#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>

std::condition_variable Cv;
std::mutex Mtx;
int i = 5;
bool Done = false;

void Waits()
{
	// 범위를 벗어나면 자동으로 뮤텍스 잠금이 해제된다.
	std::unique_lock<std::mutex> Lock(Mtx);
	std::cout << "Waiting... \n";

	/*
		void wait(std::unique_lock<std::mutex>& lock, Predicate pred)는 아래와 같은 기능을 수행한다.
		while(!pred()) // Pred() 함수가 거짓이면 반복 작업을 수행한다.
		{
			Cv.wait(Lock);
		}
	*/

	Cv.wait(Lock, []
		{
			if (i > 0)
				std::cout << "신호를 기다린다... \n";
			return  i-- == 0;
		});
	std::cout << "Finished Waiting. i == 0\n";
	Done = true;
}

void Signals()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	// 만약 i = 0; 으로 설정되어 있다면 wait() 함수가 해제된다.
	Cv.notify_one(); // wait() 함수의 호출이 없을 때 무시된다.

	std::unique_lock<std::mutex> Lock(Mtx);
	while (!Done)
	{
		std::cout << i << ". notify 신호를 전송한다...";
		Lock.unlock();
		Cv.notify_one(); // wait() 함수에 지속적으로 신호를 전송한다.
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		Lock.lock(); // 범위를 벗어나면 자동으로 뮤텍스 잠금이 해제된다.
	}
}

int main()
{
	std::thread t1(Waits), t2(Signals);
	t1.join();
	t2.join();
}