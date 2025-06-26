#include <iostream>
#include <atomic>
#include <cassert>
#include <string>
#include <thread>

std::atomic<std::string*> Ptr;
int Data;

void Producer()
{
	std::string* p = new std::string("Hello");
	Data = 42;
	std::atomic_store_explicit(&Ptr, p, std::memory_order_release);
}

void Consumer()
{
	std::string* p2 = nullptr;

	// 스레드는 어느 스레드가 먼저 작업이 수행될지 예측할 수 없다.
	// 따라서 다음과 같이 초기화값이 입력될 때까지 대기한다.
	while (!(p2 = std::atomic_load_explicit(&Ptr, std::memory_order_acquire)))
	{
		// 만약 아직 p2가 null이라면 다른 스레드로 작업을 넘긴다.
		std::this_thread::yield();
	}

	std::cout << *p2 << std::endl;
	assert(*p2 == "Hello");
	assert(Data == 42);
}

int main()
{
	std::thread t1(Producer);
	std::thread t2(Consumer);

	t1.join();
	t2.join();
}