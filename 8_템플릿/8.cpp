#include <iostream>

template<typename T1>
class String
{
	// 아래는 멤버 템플릿 함수이다.
	template<typename T2>
	T1 Compare(const T2& s);

};

template<typename T1> // 클래스 템플릿
template<typename T2> // 멤버 함수 템플릿
T1 String<T1>::Compare(const T2& s)
{

}