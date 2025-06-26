#include <cstring>
#include <iostream>

// 아래 'int i'처럼 타입이 아닌 템플릿 매개변수는 타입을 나타내는 class나 typename의 지정자를
// 사용하지 않는다.
template<int i>
class A
{
public:
	A() { memset(Array, 0, i * sizeof(int)); }
	void Print()
	{
		//템플릿 인수는 상수처럼 사용할 수 있다.
		std::cout << "size of " << i << std::endl;
		for (auto l : Array) { std::cout << l << std::endl; }
		std::cout << std::endl;
	}

private:
	int Array[i]; //배열의 크기를 템플릿 인수로 제공한다.
	const int Length = i; //배열의 크기를 상수로 사용한다.
};

int main()
{
	//명시적인 방법으로 템플릿 인수의 값을 10으로 할당하였다. 객체 생성과 함께 내부에 10의 크기를
	//갖는 배열이 생성된다.
	A<10> a;
	a.Print();
}