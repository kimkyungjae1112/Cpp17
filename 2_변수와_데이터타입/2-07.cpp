//범위가 있는 열거형 타입과 범위가 없는 열거형 타입의 차이
#include <iostream>
using namespace std;

enum Color1
{
	RED,
	GREEN,
	BLUE
};

enum class Color2
{
	GREEN,
	YELLOW,
	RED
};

int main()
{
	Color1 BackGround = RED;
	Color1 ForeGround = Color1::BLUE;
	//Color1 Color = Color2::RED; 에러

	cout << RED << GREEN << BLUE << endl;

	// Color2 열거형 타입은 아래와 같이 제한이 존재한다.
	//Color2 Stop = RED; 에러
	//Color2 Wait = YELLOW; 에러
	Color2 Go = Color2::GREEN; 

	cout << static_cast<int>(Color2::RED) << static_cast<int>(Color2::GREEN) << static_cast<int>(Color2::YELLOW) << endl;
}