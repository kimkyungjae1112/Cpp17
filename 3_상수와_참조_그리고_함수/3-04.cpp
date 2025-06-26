#include <iostream>
#include <string>
using namespace std;

int general(int i) { return i >= 0 ? i : -i; }

//C언어에서 제공하는 매크로 함수이다.
#define unsafe(i) ( (i) >= 0 ? (i) : -(i))

//인라인 함수이다.
inline int safe(int i) { return i >= 0 ? i : -i; }

//상수표현식이다.
constexpr int expr(int i){ return i >= 0 ? i : -i; }

int main()
{
	int ans, x = 0;

	// 1. 인라인 함수는 다음과 동일한 기능을 제공한다.
	ans = (x >= 0) ? x : -x;
	cout << "ans = " << ans << ", " << x << endl;

	// 2. 일반 함수를 호출하여 실행시킨 예이다.
	x = 0;
	ans = general(x++);
	cout << "general(x++) = " << ans << ", " << x << endl;

	// 3. C언어의 매크로를 실행시킨 예이다.
	x = 0;
	ans = unsafe(x++);
	cout << "unsafe(x++) = " << ans << ", " << x << endl;

	// 4. 인라인 함수를 실행시킨 예이다.
	x = 0;
	ans = safe(x++);
	cout << "safe(x++) = " << ans << ", " << x << endl;

	// 5. 상수표현식을 실행시킨 예이다.컴파일 시점에 함수의 인수로 0이 입력되는
	//    사실을 알기 때문에 컴파일 시점에 반환되는 값은 상수로 계산되어 처리된다.
	x = 0;
	ans = expr(x++);
	cout << "expr(x++) = " << ans << ", " << x << endl;
	return 0;
}