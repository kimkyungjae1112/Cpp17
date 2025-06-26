#include <iostream>
#include <cstring>

union DataValue01 //공용체를 만든다.
{
	int Vint;
	float Vfloat;
	char Vstring[4];
};

struct DataValue02 //구조체를 만든다.
{
	int Vint;
	float Vfloat;
	char Vstring[4];
};

int main()
{
	std::cout << "공용체의 크기 = " << sizeof(DataValue01) << std::endl;
	std::cout << "구조체의 크기 = " << sizeof(DataValue02) << std::endl;
}