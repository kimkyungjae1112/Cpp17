#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex Mtx;
std::condition_variable Cv;
static int Ranking = 1;	// 작업 실행 순서를 알아보기 위해 사용하는 전역 변수

void Print(int Id)
{
	// 1. 뮤텍스와 함께 unique_lock 객체를 사용하여 잠금을 설정한다.
	std::unique_lock<std::mutex> Umtx(Mtx);

	// 2. 조건 변수 클래스가 제공하는 wait() 함수를 호출하고 조건 변수의 신호를 기다린다.
	//	  wait() 함수는 내부에서 앞서 설정한 뮤텍스의 잠금을 해제시키고
	//    조건 변수를 통해 신호가 들어오기까지 대기하는 기능을 제공한다.
	Cv.wait(Umtx);
	std::cout << Ranking++ << ". Thread " << Id << '\n';
	Umtx.unlock();
}

/*
조건 변수가 신호를 받으면, 작업을 수행하기 전에 가장 먼저 wait() 함수 내부에서 뮤텍스에 대한 잠금을 다시 설정하고
임계 구역으로 진입하여 작업을 수행한다. 여기 예에서는 단지 콘솔 화면에 자기 자신의 쓰레드  아이디를 출력하는 작업을
수행한다.

작업이 완료되어 프로그램 제어가 지역 범위를 벗어난다면 std::unique_lock 클래스의 특성에 따라 뮤텍스의 잠금이 자동으로
해제되는 동시에 객체가 소멸된다. 위의 일반 스레드의 레이스 경쟁을 주도할 메인 스레드는 아래와 같은 작업을 수행한다.
*/

int main()
{
	std::thread Threads[10];
	
	for (int i = 0; i < 10; ++i)
	{
		// 3. 작업을 수행할 스레드를 생성하고 스레드를 실행시킨다.
		Threads[i] = std::thread(Print, i);
	}

	std::cout << "10개의 쓰레드가 레이스 경쟁을 펼친다.\n";
	// 모든 스레드가 wait() 함수를 호출할 때까지 잠시 대기 한다.
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	/*
		아래 뮤텍스 잠금이 설정되면, 역으로 다른 모든 일반 쓰레드에서 wait() 함수를 호출하고
		뮤텍스의 잠금을 해제시켰다는 의미가 된다. 뮤텍스 잠금을 설정하고 임계 구역으로 진입하여
		조건 변수를 통해 작업 시작을 알린다.
	*/

	{
		std::unique_lock<std::mutex> Umtx(Mtx);
		Cv.notify_all();	// 모든 스레드에 신호를 보낸다.
	}	// 뮤텍스가 해제된다.
	
	for (auto& Th : Threads) Th.join();
	return 0;

	// 메인 스레드가 보낸 신호는 모든 일반 쓰레드에 거의 동시에 신호를 보냈지만, 그 가운데 가장 먼저 신호를 받은
	// 쓰레드가 가장 먼저 해제된 뮤텍스에 대한 잠금을 설정한다. 
}

