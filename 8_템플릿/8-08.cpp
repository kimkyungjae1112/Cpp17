#include <iostream>

template<class T>
class Form
{
public:
	Form(T* t) : _t(t) {}
	void Print()
	{
		std::cout << *_t << std::endl;
	}

private:
	T* _t;
};

// �Ʒ��� ���� char* Ÿ���� ����Ͽ� ���ø� ��ȯ�� �����Ѵٸ�, ��ȯ �μ���
// ����� ������ Ÿ�Կ� ���� �Ʒ� ���ø��� ���� ���ø����� �켱������ ����ȴ�.
template<>
class Form<char*>
{
public:
	Form(char* t) : _t(t) {}
	void Print()
	{
		std::cout << "Form<char*> : " << _t << std::endl;
	}

private:
	char* _t;
};

int main()
{
	int i = 157;
	Form<int> form1(&i); // �⺻ ���ø��� �����Ѵ�.

	char c[10] = "string1";
	// char* �μ��� ����Ͽ� ���ø� Ư��ȭ�� Ŭ���� ���ø��� �ν��Ͻ��� �����.
	Form<char*> form2(c);

	form1.Print();
	form2.Print();
}