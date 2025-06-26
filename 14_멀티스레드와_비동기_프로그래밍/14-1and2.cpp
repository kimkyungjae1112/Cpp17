#include <thread>
#include <chrono>
#include <string>
#include <iostream>

// 아래는 스레드로 실행시킬 함수이다.
void InThread(std::string Name)
{
	std::this_thread::sleep_for(std::chrono::seconds(1)); // 1초동안 스레드의 실행을 보류한다.
	// 스레드 아이디를 화면에 출력시킨다.
	// 동기화가 필요하다.
	std::cout << Name << " 스레드 아이디 : " << std::this_thread::get_id() << std::endl;
}

int main()
{
	// 보통 CPU 코어 개수는 실행 가능한 스레드 개수로 인식한다.
	std::cout << "하드웨어 CPU 코어수 : " << std::thread::hardware_concurrency() << std::endl;

	// 1. 스레드 생성자를 사용하여 스레드 객체를 생성한다.
	std::thread Thread1(InThread, "Thread1");

	// 2. 아래 디폴트 생성자는 의미없는 작업이다.
	std::thread Thread2;
	Thread2 = std::thread(InThread, "Thread2");

	// 3. 람다 함수를 만들어 스레드로 실행시킨다.
	std::thread Thread3([&](int Param)
		{
			std::cout << "Thread3 : " << std::this_thread::get_id() << std::endl;
			for (int i = 0; i < 5; ++i)
				std::cout << "Thread3 Parameter : " << Param << std::endl;
		}, 4);

	Thread1.join();
	Thread2.join();
	Thread3.join();

	return 0;
}