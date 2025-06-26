#include <iostream>
#include <string>

int main()
{
	const char* cc = "문자열을 입력합니다. This is a string";
	std::string str; // string 타입으로 변수를 선언한다.

	str = cc; // char 타입의 문자열을 대입하더라도 사용이 가능하다.
	std::cout << "str = " << str.data() << ", 문자열의 크기는 " << str.length() << std::endl;

	str = "클래스 내부에서 공간을 잡는다.";
	// 정수처럼 연산도 가능하다. 아래는 문자열을 이어서 쓰는 방법이다.
	str += " 따라서 별도 메모리 공간을 잡지 않아도 사용이 가능하다.";
	std::cout << "str = " << str.data() << ", 문자열의 크기는 " << str.length() << std::endl;
	return 0;
}

/*

출력 결과

str = 문자열을 입력합니다. This is a string, 문자열의 크기는 37
str = 클래스 내부에서 공간을 잡는다. 따라서 별도 메모리 공간을 잡지 않아도 사용이 가능하다., 문자열의 크기는 85

*/