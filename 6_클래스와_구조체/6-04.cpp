#include <iostream>

using std::cout;
using std::endl;

class Something
{
private:
	static int iValue;			// 정적 멤버 변수이다.
	static const int ciValue;   // 정적 멤버 상수이다.

public:
	// 정적 함수는 오로지 정적 멤버 변수나 정적 멤버 상수 그리고
	// 정적 함수만을 호출할 수 있다.
	// 정적 함수는 객체가 생성되지 않더라도 호출이 가능하므로 초기화 되어 있지 않은
	// 일반 멤버 변수나 함수를 사용할 수 없다.
	static int GetValue() { return iValue; }
	static const int GetConst() { return ciValue; }
};

int Something::iValue = 1; // 정적 멤버 변수를 초기화한다.
const int Something::ciValue = 10; // 정적 상수 멤버 변수를 초기화한다.

int main()
{
	cout << "Something::GetValue() = " << Something::GetValue() << endl;
	cout << "Something::GetConst() = " << Something::GetConst() << endl;
}