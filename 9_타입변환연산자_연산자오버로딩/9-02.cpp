#include <iostream>

enum Days
{
	Sunday = 0, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
};

enum class Months : short
{
	Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

const char* Week[] = { "Sunday", "Monday", "Tuesday", 
						"Wednesday", "Thursday", "Friday", "Saturday" };


// 열거형 타입의 요소로 제공되는 주의 이름을 문자열로 반환한다.
const char* DayName(Days Day)
{
	if (Day < Sunday || Day > Saturday)
		return "알 수 없는 날";
	return Week[Day];
}

int main()
{
	Months ThisMonth = Months::Dec;

	Days Today = static_cast<Days>(ThisMonth); // == Days Today = (Days) ThisMonth;
	std::cout << DayName(Today) << "는 " << Today + 1 << "번째 요일이다." << std::endl;

	Months NextMonth = (Months)((short)Months::Dec - 12 + 1);
	Today = static_cast<Days>(NextMonth);
	std::cout << DayName(Today) << "는 " << Today + 1 << "번째 요일이다." << std::endl;

	// 열거형 타입의 요소로부터 int 또는 float 으로 변환은 다음과 같다.
	float One = static_cast<float>(Today);
	std::cout << DayName(Today) << "는 " << One + 1 << "번째 요일이다." << std::endl;

	return 0;
}