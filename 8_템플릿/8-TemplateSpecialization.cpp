#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

// 클래스 템플릿을 선언하거나 정의한다.
template<typename T>
inline std::string Stringify(T const& x)
{
	std::ostringstream out;
	out << x;
	return out.str();
}

// 아래는 전체 템플릿 특수화로 별도 템플릿 매개변수를 지정하지 않는다. 그리고 템플릿 인수를 지정하여
// 위의 템플릿 매개변수와 또 다른 형식의 함수 오버로딩처럼 사용한다.
template<>
inline std::string Stringify<bool>(bool const& x)
{
	std::ostringstream out;
	out << std::boolalpha << x;
	return out.str();
}

template<>
inline std::string Stringify<double>(double const& x)
{
	std::ostringstream out;
	const int Sigdigits = std::numeric_limits<double>::digits10;
	out << std::setprecision(Sigdigits) << x;
	return out.str();
}

int main()
{
	std::cout << Stringify<int>(100) << ", " << Stringify<bool>(true) << ", " <<
		Stringify<double>(23.65) << std::endl;
}