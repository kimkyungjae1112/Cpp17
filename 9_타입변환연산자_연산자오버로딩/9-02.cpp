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


// ������ Ÿ���� ��ҷ� �����Ǵ� ���� �̸��� ���ڿ��� ��ȯ�Ѵ�.
const char* DayName(Days Day)
{
	if (Day < Sunday || Day > Saturday)
		return "�� �� ���� ��";
	return Week[Day];
}

int main()
{
	Months ThisMonth = Months::Dec;

	Days Today = static_cast<Days>(ThisMonth); // == Days Today = (Days) ThisMonth;
	std::cout << DayName(Today) << "�� " << Today + 1 << "��° �����̴�." << std::endl;

	Months NextMonth = (Months)((short)Months::Dec - 12 + 1);
	Today = static_cast<Days>(NextMonth);
	std::cout << DayName(Today) << "�� " << Today + 1 << "��° �����̴�." << std::endl;

	// ������ Ÿ���� ��ҷκ��� int �Ǵ� float ���� ��ȯ�� ������ ����.
	float One = static_cast<float>(Today);
	std::cout << DayName(Today) << "�� " << One + 1 << "��° �����̴�." << std::endl;

	return 0;
}