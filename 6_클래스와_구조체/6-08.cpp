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
	// �⺻ Ŭ������ ���� �����ϰ� �ڽ��� ����� �ʱ�ȭ��Ű�� ���� ���⿡ ����.
	Student(std::string sName, std::string sId) : Person(sName), sId(sId) {}

	std::string& GetID() { return sId; }

private:
	std::string sId;
};

int main()
{
	Student S1("ȫ�浿", "20056");

	std::cout << "�̸� : " << S1.GetName() << ", �й� : " << S1.GetID() << std::endl;

	return 0;
}