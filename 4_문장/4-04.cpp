#include <stdio.h>
#include <iostream>
#include <string>
#include "4-04.h"

int MyGlobal = 0;

namespace MyNamespace
{
	const int OPEN = 1;
	const int CLOSE = 0;

	void Door::Open()
	{
		State(OPEN);
	}

	void Door::Close()
	{
		State(CLOSE);
	}

	void Door::ShowState() const
	{
		printf("현재 문의 상태 : ");
		std::cout << ((IState == OPEN) ? "OPEN" : "CLOSE") << std::endl;
	}

	void Door::SetName(std::string Str)
	{
		Name = Str;
	}

	std::string Door::GetName() const
	{
		return Name;
	}
}

int main()
{
	MyNamespace::Door D;

	D.Open();
	D.ShowState();

	MyGlobal = 1;
	std::cout << MyGlobal << std::endl;
	return 0;
}