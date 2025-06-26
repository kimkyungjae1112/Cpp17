#include <cstdio>
#include <iostream>
#include <string>

class Box
{
public:
	Box(int Width = 0, int Length = 0, int Height = 0) : 
		Width(Width), Length(Length), Height(Height) 
	{
		std::cout << "Box( ," << Width << ", " << Length << ", " << Height <<
			" ) �����ڰ� ȣ�� �Ǿ����ϴ�." << std::endl;
	}
	~Box()
	{
		std::cout << "Box �Ҹ��ڰ� ȣ��Ǿ����ϴ�." << std::endl;
	}

	// �Ʒ� �Լ� ȣ�� ������ �����ε��� �μ��� void Ÿ���� �� ����ϴ� �Լ��̴�.
	// ���� �ڽ��� ���Ǹ� ����Ͽ� ��ȯ�Ѵ�.
	int operator()()
	{
		return Width * Length * Height;
	}

	// �Ʒ� �Լ� ȣ�� ������ �����ε��� ���̸� ������ �� �ִ� �μ��� �����Ѵ�.



private:
	int Width;
	int Length;
	int Height;

};