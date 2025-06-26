#include <stdexcept>
#include <iostream>

void CopyObject(const char* Original)
{
	if (nullptr == Original)
	{
		// 인수로 전달된 객체가 NULL 이라면 예외를 발생시킨다.

		throw std::runtime_error("인수가 NULL이다.");
	}

	std::cout << Original << std::endl;
}

int main()
{
	try
	{
		char* Name = nullptr;
		CopyObject(Name);
	}
	catch (int e)
	{
		std::cerr << e << std::endl;
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "모든 Exception 처리" << std::endl;
	}

	std::cout << "프로그램 종료!" << std::endl;
	return 0;
}

