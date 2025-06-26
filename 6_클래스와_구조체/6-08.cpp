#include <iostream>
#include <string>

struct Person
{
public:
	Person(std::string sName) : sName(sName) {}

	std::string& GetName() { return sName; }

private:
	std::string sName;
};

class Student : public Person
{
public:
	// 기본 클래스를 먼저 생성하고 자신의 멤버를 초기화시키는 것이 보기에 좋다.
	Student(std::string sName, std::string sId) : Person(sName), sId(sId) {}

	std::string& GetID() { return sId; }

private:
	std::string sId;
};

int main()
{
	Student S1("홍길동", "20056");

	std::cout << "이름 : " << S1.GetName() << ", 학번 : " << S1.GetID() << std::endl;

	return 0;
}