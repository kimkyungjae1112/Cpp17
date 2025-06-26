#include <iostream>

class Person
{
public:
	Person(std::string N, int A) : Name(N), Age(A) {}

	bool Compare(const Person& P)
	{
		// Name�� Age�� private���� ����Ǿ� �ִ��ϴ��� ���� Ŭ�����̹Ƿ�
		// �Ʒ��� ���� �ڽŰ� �μ� ��� ����� �����ϴ�.
		return (this->Age < P.Age) ? false : true;
	}

private:
	std::string Name;
	int Age;
};