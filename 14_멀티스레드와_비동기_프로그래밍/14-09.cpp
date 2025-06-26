#include <iostream>
#include <mutex>

std::mutex Mtx;
int Global;
#define MAX_TRHREADS 2

/* 스레드에서 호출되는 함수이다. */

void Function(int Func, int Loops)
{
	/* 인수로 제공된 loops만큼 지속적으로 1을 Global 변수에 합한다.*/
	for (int i = 0; i < Loops; ++i)
	{
		Mtx.lock();			// 입장 구역
		++Global;			// 임계 구역
		Mtx.unlock();		// 퇴장 구역
		if ((i % 10) == 0) std::this_thread::yield();
	}
	printf("%d. Global = %d\n", Func, Global);
}

int main()
{
	std::thread T[MAX_TRHREADS];

	// 반복 계산에 사용하는 Loops는 10000으로 설정
	for (int i = 0; i < MAX_TRHREADS; ++i)
	{
		/* 동일한 함수를 2개의 스레드로 만들어 실행시킨다. */
		T[i] = std::thread(Function, i, 10000);
	}

	for (int i = 0; i < MAX_TRHREADS; ++i)
	{
		T[i].join();
	}

	printf("Global = %d\n", Global);
	return 0;
}