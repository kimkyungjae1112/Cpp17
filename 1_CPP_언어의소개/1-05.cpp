#pragma warning(disable: 4996) // 비주얼 스튜디오 사용 시 추가한다.
#include <cstring>
#include <cstdlib>
#include <iostream>

int main()
{
	const char* cc = "문자열을 입력합니다. This is a string";
	char cb[17]; // 문자열을 만들 때 16개 문자와 마지막 문자로 NULL를 사용한다.
	char* str; // 문자열 포인터다.

	memcpy(cb, cc, 17); // 만약 'strcpy(cb, cc);'를 사용한다면 에러가 발생한다.
	str = (char*)malloc(strlen(cc) + 1); // 문자열을 저장하기 위해 메모리 공간을 할당받는다.
	strcpy(str, cc);

	// 아래와 같이 '\0'이 없기 때문에 변수의 크기를 넘어 일부 데이터가 깨지는 에러가 발생한다.
	std::cout << "cc = " << cc << ", 문자열의 크기는 " << strlen(cc) << std::endl;
	std::cout << "cb = " << cb << ", 문자열의 크기는 " << strlen(cb) << std::endl;
	std::cout << "str = " << str << ", 문자열의 크기는 " << strlen(str) << std::endl;
	free(str);
}


/* 

출력결과

cc = 문자열을 입력합니다. This is a string, 문자열의 크기는 37
cb = 문자열을 입력합니儆儆儆儆儆儆儆儆儆儆儆儆儆儆儆?2解?, 문자열의 크기는 54
str = 문자열을 입력합니다. This is a string, 문자열의 크기는 37

*/