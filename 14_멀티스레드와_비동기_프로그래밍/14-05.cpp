#include <thread>
#include <iostream>

thread_local int Local; // 스레드 지역 변수
int Global; // 일반 전역 변수
#define MAX_THREADS 2

// 전역 변수를 인수로 넘겨받아 처리한다.
void Function(int Func, int Glocal, int Loops)
{
	Local = Glocal;
	for (int i = 0; i < Loops; ++i)
	{
		++Local;
		if (i % 10 == 0)
		{
			std::this_thread::yield();
			printf("%d. 의 i = %d\n", Func, i);
		}
	}

	// 작업이 완료된 이후에 전역 변수에 합산한다.
	Global += Local;
	printf("%d. Global = %d\n", Func, Global);
}

int main()
{
	std::thread T[MAX_THREADS];
	Global = 0;
	for (int i = 0; i < MAX_THREADS; ++i)
	{
		// 전역 변수를 인수로 넘긴다.
		T[i] = std::thread(Function, i, Global, 10000);
	}

	for (int i = 0; i < MAX_THREADS; ++i)
	{
		T[i].join();
	}

	printf("Global = %d\n", Global);
}