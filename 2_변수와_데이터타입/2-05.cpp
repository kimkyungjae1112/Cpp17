#include <iostream>
#include <cstring>

union DataValue01 //����ü�� �����.
{
	int Vint;
	float Vfloat;
	char Vstring[4];
};

struct DataValue02 //����ü�� �����.
{
	int Vint;
	float Vfloat;
	char Vstring[4];
};

int main()
{
	std::cout << "����ü�� ũ�� = " << sizeof(DataValue01) << std::endl;
	std::cout << "����ü�� ũ�� = " << sizeof(DataValue02) << std::endl;
}