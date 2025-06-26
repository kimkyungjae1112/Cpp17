//상수 표현식은 일종의 inline 함수처럼 사용한다.
#include <iostream>
using namespace std;

constexpr unsigned long fibonacci(unsigned long i)
{
	return (i <= 1ul) ? i : (fibonacci(i - 1) + fibonacci(i - 2));
}

int main()
{
	// 아래 문장은 'unsigned long l = 610;'와 동일하게 처리된다.
	// 함수의 인수롤 상수를 입력하기 때문에 컴파일 시점에 상수로 인식된다.
	unsigned long i = fibonacci(15);
	cout << i << " = fibonacci(15)" << endl;

	constexpr int z = fibonacci(15);
	cout << z << " : z의 값" << endl;
	
	int a;
	cin >> a;
	// 에러! constexpr int y = fibonacci(a);

	return 0;
}