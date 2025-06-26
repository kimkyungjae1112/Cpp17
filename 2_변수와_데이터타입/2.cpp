#include <iostream>

void Test()
{
	static int var;
	++var;

	std::cout << var << std::endl;
}

int main()
{
	Test();
	Test();
	//int a = var; 에러 발생

	return 0;
}

// 함수 내부에 선언된 정적 변수는 마치 함수 외부에 선언된 전역 변수처럼 사용된다.
// 하지만 함수 내부에 설정된 정적 변수는 전역 변수처럼 사용하더라도 함수 외부에서 호출될 수 없다.