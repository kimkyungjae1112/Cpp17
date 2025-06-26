#include <iostream>

struct Something
{
	static int Svalue; //정적 멤버를 선언하다.
	static int GetSvalue() { return Svalue; } //정적 멤버 함수를 정의한다.

	int Value; //일반 멤버 변수를 선언한다.
	int GetValue() { return Value; } //일반 멤버 함수를 정의한다.
};

// 아래는 정적 멤버 변수를 초기화시킬 때 다음처럼 범위 확인 연산자를 사용한다.
int Something::Svalue = 1;

int main()
{
	// 정적 멤버 함수는 구조체로 선언된 변수가 없더라도 아래처럼 호출이 가능하다.
	std::cout << Something::GetSvalue() << std::endl;

	// 정적 멤버 변수가 아닌 구조체의 일반 멤버 변수는 변수 선언과 함께 다음과 같이 100으로 Value 멤버 변수를 초기화시킬 수 있다.
	Something S = { 100 };

	// 정적 멤버 함수든 일반 멤버 함수든 무관하게 함수의 호출은 다음과 같다.
	std::cout << S.GetSvalue() << " , " << S.GetValue() << std::endl;
	return 0;
}