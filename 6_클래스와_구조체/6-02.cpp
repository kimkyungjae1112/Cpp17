#include <iostream>

class SimpleClass
{
public:
	int Val;
};

int main()
{
	SimpleClass SC;
	SC.Val = 5;
	std::cout << SC.Val << std::endl;
	return 0;
}