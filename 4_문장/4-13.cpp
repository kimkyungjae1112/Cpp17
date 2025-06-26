#include <stdexcept>
#include <iostream>

void CopyObject(const char* Original)
{
	if (nullptr == Original)
	{
		// �μ��� ���޵� ��ü�� NULL �̶�� ���ܸ� �߻���Ų��.

		throw std::runtime_error("�μ��� NULL�̴�.");
	}

	std::cout << Original << std::endl;
}

int main()
{
	try
	{
		char* Name = nullptr;
		CopyObject(Name);
	}
	catch (int e)
	{
		std::cerr << e << std::endl;
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "��� Exception ó��" << std::endl;
	}

	std::cout << "���α׷� ����!" << std::endl;
	return 0;
}

