#include <iostream>
#include <future>
#include <thread>
#include <numeric>
#include <vector>
#include <functional>

// 3. 아래 함수는 스레드로 실행할 함수
void Accumulate(std::vector<int>::iterator First, std::vector<int>::iterator Last, std::promise<int>&& Accumulate_Promise)
{
	int Sum = std::accumulate(First, Last, 0);
	// 6. std::promise 객체의 set_value() 함수를 사용하여 std::future 객체에 함수의 실행 결과값을 전달한다.
	Accumulate_Promise.set_value(Sum);
}

std::future<int> Launch_Promise(std::vector<int>::iterator First, std::vector<int>::iterator Last)
{
	// 1. std::promise 객체를 생성한다.
	std::promise<int> Accumulate_Promise;

	// 2. future 객체를 반환받아 사용한다.
	std::future<int> Result = Accumulate_Promise.get_future();

	// 3. 스레드 객체를 생성하고 함수의 인수로 std::promise 객체를 전달한다.
	std::thread Work_Thread(Accumulate, First, Last, std::move(Accumulate_Promise));
	Work_Thread.detach();
	return Result;
}

int main()
{
	int Total = 0;
	std::vector<int> Numbers = { 1,2,3,4,5,6,7,8,9,10 };

	// promise 객체가 작업할 환경을 만들고 future 객체를 반환받는다.
	std::future<int> s[2];
	s[0] = Launch_Promise(Numbers.begin(), Numbers.begin() + 6);
	s[1] = Launch_Promise(Numbers.begin() + 6, Numbers.end());

	for (int i = 0; i < Numbers.size(); ++i)
	{
		// 5. 스레드의 작업 결과를 받아 처리한다.
		int w = s[i].get();
		std::cout << "promise-" << i << " : " << w << '\n';
		Total += w;
	}
		
	std::cout << "합계 : " << Total << '\n';
}