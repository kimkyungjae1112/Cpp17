#include <iostream>

// 타입이 아닌 템플릿 매개변수를 참조로 사용한다.
template<int& ri>
struct Simple
{
	/*Simple()
	{
		printf("객체 생성 시 ri는 %d 이다.\n", ri);
	}
	~Simple()
	{
		printf("객체 소멸 시 ri는 %d 이다.\n", ri);
	}*/
};

int i = 1;

int main()
{
	// 반드시 전역 변수를 사용하여 객체를 생성해야 한다. 만약 지역 변수를 사용한다면, 컴파일 시점에
	// 데이터를 확정하지 못해 에러가 발생한다.
	Simple<i> S;
	i = 0;
	return 0;
}