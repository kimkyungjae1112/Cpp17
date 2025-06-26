#include <iostream>
#include <deque>
#include <vector>

template<typename T, template<typename ELEM> class CONT = std::deque>
class Stack
{
public:
	void Push(T const& a)
	{
		Elems.push_back(a);
	}
	void Pop()
	{
		Elems.pop_back();
	}
	const T& Top() const
	{
		return Elems.back();
	}
	bool empty() const
	{
		return Elems.empty();
	}

private:
	CONT<T> Elems;
};

// Allocator 클래스 템플릿을 선언한다.
template<typename Type>
class Allocator
{

};

// 위의 선언된 클래스 템플릿을 Allocator 매개변수의 디폴트 타입으로 만든다. 만약 템플릿을 디폴트 데이터
// 타입으로 사용한다면, 다음과 같이 템플릿 변환으로 만들어야 사용이 가능하다.
template<typename Type, typename allocator = Allocator<Type>>
class Vector
{

};

int main()
{
	// allocator 매개변수에 대응하는 데이터 타입을 명시하지 않는다면,
	// allocator 인수의 타입은 자동적으로 allocator<int> 타입이 된다.
	Vector<int> vec1;
	Vector<int, double> vec2;


	// 만약 템플릿 매개변수를 인수로 사용한다면 std::vector 클래스 템플릿을 명시해주어야 한다.
	Stack<int, std::vector> vStack;
	vStack.Push(1);
	vStack.Push(2);

	while (vStack.empty() == false)
	{
		std::cout << vStack.Top() << std::endl;
		vStack.Pop();
	}
}

// size 매개변수는 '타입이 아닌 템플릿 매개변수'이다.
template<class T, int size> 
class MyFile
{
public:
	MyFile() {}

private:
	T* FilePos;
	static int Array[size]; // 타입이 아닌 매개변수를 사용해 배열의 크기를 지정한다.
};