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

// Allocator Ŭ���� ���ø��� �����Ѵ�.
template<typename Type>
class Allocator
{

};

// ���� ����� Ŭ���� ���ø��� Allocator �Ű������� ����Ʈ Ÿ������ �����. ���� ���ø��� ����Ʈ ������
// Ÿ������ ����Ѵٸ�, ������ ���� ���ø� ��ȯ���� ������ ����� �����ϴ�.
template<typename Type, typename allocator = Allocator<Type>>
class Vector
{

};

int main()
{
	// allocator �Ű������� �����ϴ� ������ Ÿ���� ������� �ʴ´ٸ�,
	// allocator �μ��� Ÿ���� �ڵ������� allocator<int> Ÿ���� �ȴ�.
	Vector<int> vec1;
	Vector<int, double> vec2;


	// ���� ���ø� �Ű������� �μ��� ����Ѵٸ� std::vector Ŭ���� ���ø��� ������־�� �Ѵ�.
	Stack<int, std::vector> vStack;
	vStack.Push(1);
	vStack.Push(2);

	while (vStack.empty() == false)
	{
		std::cout << vStack.Top() << std::endl;
		vStack.Pop();
	}
}

// size �Ű������� 'Ÿ���� �ƴ� ���ø� �Ű�����'�̴�.
template<class T, int size> 
class MyFile
{
public:
	MyFile() {}

private:
	T* FilePos;
	static int Array[size]; // Ÿ���� �ƴ� �Ű������� ����� �迭�� ũ�⸦ �����Ѵ�.
};