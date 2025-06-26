#include <iostream>

static int i = 0;

template<typename T>
void ParamCheck(T&& s)
{
	// is_reference Ŭ���� ���ø��� s�� ������ Ÿ���� ������� value ������ true�� ��ȯ�Ѵ�.
	if (std::is_reference<T&&>::value)
	{
		// T&&�� lvalue ������� value ����� true�� ��ȯ�Ѵ�.
		if (std::is_lvalue_reference<T&&>::value)
		{
			// Ÿ���� ��� Ÿ���̶�� �����ϰ� value�� true�� ��ȯ�Ѵ�.
			if (std::is_const<T&&>::value)
			{
				std::cout << ++i << ". " << s << " �μ��� 'const T&' Ÿ���̴�.\n";
			}
			else
			{
				std::cout << ++i << ". " << s << " �μ��� 'T&' Ÿ���̴�.\n";
			}
		}
		else
		{
			std::cout << ++i << ". " << s << " �μ��� 'T&&' Ÿ���̴�.\n";
		}
	}
	else
	{
		std::cout << ++i << ". " << s << " �μ��� 'T' Ÿ���̴�.\n";
	}
}

int main()
{
	// 1. (char[5]) Ÿ���� ����Ҹ� �����Ͽ� ���޵ǹǷ� 'T&' Ÿ������ �νĵȴ�.
	ParamCheck("���ͷ�");

	// 2. �ӽ� ����Ҹ� �����Ѵ�. �ӽ� ����Ҵ� 'T&&' Ÿ������ �νĵȴ�.
	ParamCheck(std::string{ "������" });

	// 3. s3 ������ ���� ó���� ���� 'T&' Ÿ������ ó���Ѵ�.
	std::string s3{ "�Ϲ� ����" };
	ParamCheck(s3);

	// 4. const �����ڸ� ����Ͽ� lvalue ������ ����� ����ٸ�, 'T&' Ÿ������ ó���Ѵ�.
	const std::string& s4{ "const ���" };
	ParamCheck(s4);
	
	// 5. ������ ���� move() �Լ��� ����Ѵٸ� 'T&&' Ÿ������ �νĵȴ�.
	std::string ss = std::string("std::move(") + s3 + std::string(")");
	std::string& s5{ ss };

	// 6. rvalue ���� Ÿ������ �����Ͽ����� ���� �Ϲ� ������ ��ϵȴ�. ����
	// �μ��� 'T&'���� ���޵ȴ�.
	std::string&& s6 = std::string("���Կ����ڿ� ������");
	ParamCheck(s6);

	std::cout << std::endl;
	return 0;
}