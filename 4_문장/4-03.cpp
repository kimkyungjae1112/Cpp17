#include <iostream>

namespace
{
	void SampleMethod()
	{
		std::cout << "���� ���ӽ����̽� �� SampleMethod" << std::endl;
	}
}

namespace Sample
{
	void SampleMethod()
	{
		::SampleMethod();
		std::cout << "Sample ���ӽ����̽� �� SampleMethod" << std::endl;
	}
}

int main()
{
	Sample::SampleMethod();
	SampleMethod();
	::SampleMethod();
}