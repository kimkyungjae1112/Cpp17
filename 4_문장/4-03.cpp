#include <iostream>

namespace
{
	void SampleMethod()
	{
		std::cout << "무명 네임스페이스 내 SampleMethod" << std::endl;
	}
}

namespace Sample
{
	void SampleMethod()
	{
		::SampleMethod();
		std::cout << "Sample 네임스페이스 내 SampleMethod" << std::endl;
	}
}

int main()
{
	Sample::SampleMethod();
	SampleMethod();
	::SampleMethod();
}