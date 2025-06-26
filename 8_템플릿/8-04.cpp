#include <cstring>
#include <iostream>

// �Ʒ� 'int i'ó�� Ÿ���� �ƴ� ���ø� �Ű������� Ÿ���� ��Ÿ���� class�� typename�� �����ڸ�
// ������� �ʴ´�.
template<int i>
class A
{
public:
	A() { memset(Array, 0, i * sizeof(int)); }
	void Print()
	{
		//���ø� �μ��� ���ó�� ����� �� �ִ�.
		std::cout << "size of " << i << std::endl;
		for (auto l : Array) { std::cout << l << std::endl; }
		std::cout << std::endl;
	}

private:
	int Array[i]; //�迭�� ũ�⸦ ���ø� �μ��� �����Ѵ�.
	const int Length = i; //�迭�� ũ�⸦ ����� ����Ѵ�.
};

int main()
{
	//������� ������� ���ø� �μ��� ���� 10���� �Ҵ��Ͽ���. ��ü ������ �Բ� ���ο� 10�� ũ�⸦
	//���� �迭�� �����ȴ�.
	A<10> a;
	a.Print();
}