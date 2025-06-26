#include <cstdio>
#include <iostream>
#include <string>

class Box
{
public:
	Box(int Width = 0, int Length = 0, int Height = 0) : 
		Width(Width), Length(Length), Height(Height) 
	{
		std::cout << "Box( ," << Width << ", " << Length << ", " << Height <<
			" ) 생성자가 호출 되었습니다." << std::endl;
	}
	~Box()
	{
		std::cout << "Box 소멸자가 호출되었습니다." << std::endl;
	}

	// 아래 함수 호출 연산자 오버로딩은 인수가 void 타입일 때 사용하는 함수이다.
	// 예는 박스의 부피를 계산하여 반환한다.
	int operator()()
	{
		return Width * Length * Height;
	}

	// 아래 함수 호출 연산자 오버로딩은 높이를 수정할 수 있는 인수를 제공한다.



private:
	int Width;
	int Length;
	int Height;

};