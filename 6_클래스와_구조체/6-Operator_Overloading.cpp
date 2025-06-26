#include <iostream>

struct Simple
{
	// 객체를 생성하기 위해 메모리 공간을 확보하는 new 연산자 오버로딩이다.
	// new 연산자 오버로딩은 객체 생성 이전에 호출되는 연산자이므로 static 으로
	// 선언해주어야 한다.

	static void* operator new(std::size_t sz)
	{
		std::cout << "new called.\n";

		// 전역 네임스페이스 내 존재하는 new 연산자를 호출한다.
		return ::operator new(sz);
	}

	// 확보한 메모리 공간을 운영체제에 반환하는 delete 연산자 오버로딩이다.
	static void operator delete(void* ptr)
	{
		std::cout << "delete called.\n";

		::operator delete(ptr);
	}
};

int main()
{
	Simple* simple = new Simple;

	delete simple;
}