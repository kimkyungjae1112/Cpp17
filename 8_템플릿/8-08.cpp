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

// 아래와 같이 char* 타입을 사용하여 템플릿 변환을 적용한다면, 변환 인수로
// 사용한 데이터 타입에 대해 아래 템플릿이 위의 템플릿보다 우선적으로 적용된다.
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
	Form<int> form1(&i); // 기본 템플릿을 적용한다.

	char c[10] = "string1";
	// char* 인수를 사용하여 템플릿 특수화된 클래스 템플릿의 인스턴스를 만든다.
	Form<char*> form2(c);

	form1.Print();
	form2.Print();
}