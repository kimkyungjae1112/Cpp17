#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#define MAX_THREADS 3

class ThreadSafeCounter
{
public:
	ThreadSafeCounter() = default;

	// 다수의 스레드로부터 멤버 변수의 데이터를 읽을 때
	inline unsigned int Get() const
	{
		std::shared_lock Lock(Mutex);
		return Value;
	}

	// 스레드가 데이터를 저장할 때 사용
	void Increment()
	{
		std::unique_lock Lock(Mutex);
		Value++;
	}

private:
	mutable std::shared_mutex Mutex;
	unsigned int Value = 0;
};

int main()
{
	std::shared_mutex Guard;
	ThreadSafeCounter Counter;
	std::thread T[MAX_THREADS];

	auto IncrementAndPrint = [&]()
		{
			for (int i = 0; i < 3; ++i)
			{
				Counter.Increment();
				unsigned int C = Counter.Get();

				Guard.lock();
				std::cout << std::this_thread::get_id() << ", " << C << std::endl;
				Guard.unlock();
			}
		};

	for (int i = 0; i < MAX_THREADS; ++i)
	{
		T[i] = std::thread(IncrementAndPrint);
	}

	for (int i = 0; i < MAX_THREADS; ++i)
	{
		T[i].join();
	}
	return 0;
}