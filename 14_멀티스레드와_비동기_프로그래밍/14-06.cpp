#include <thread>
#include <atomic>

std::atomic<int> Global; // 전역 원자성 변수이다.
#define MAX_THREADS 2

/* 스레드로 실행되는 함수이다. */
void Function(int Func, int Loops)
{
	/* 인수로 제공된 Loops만큼 지속적으로 1을 Global 변수에 합한다. */
	for (int i = 0; i < Loops; ++i)
	{
		++Global;
		if (i % 10 == 0)
		{
			std::this_thread::yield();
		}
	}

	printf("%d. Global : %d\n", Func, Global.load());
}

int main()
{
	std::thread T[MAX_THREADS];
	Global.store(0, std::memory_order_relaxed);
	for (int i = 0; i < MAX_THREADS; ++i)
	{
		T[i] = std::thread(Function, i, 10000);
	}

	for (int i = 0; i < MAX_THREADS; ++i)
	{
		T[i].join();
	}

	printf("Global = %d\n", Global.load());
	return 0;
}