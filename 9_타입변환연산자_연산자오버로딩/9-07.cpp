#include <iostream>

class Person
{
public:
	Person(std::string N, int A) : Name(N), Age(A) {}

	bool Compare(const Person& P)
	{
		// Name과 Age는 private으로 선언되어 있다하더라도 같은 클래스이므로
		// 아래와 같이 자신과 인수 모두 사용이 가능하다.
		return (this->Age < P.Age) ? false : true;
	}

private:
	std::string Name;
	int Age;
};