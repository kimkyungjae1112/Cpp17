#include <iostream>
#include <locale>

int main(void)
{
	//화면에 정상 출력하려면 운영체제에서 사용하는 유니코드에 맞추어 인코딩해 주어야 한다.
	//아니면 정상적으로 출력할 수 없게 된다.
#if defined __linux__ || defined __CYGWIN__
#else

}