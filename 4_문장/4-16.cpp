#include <stdexcept>
#include <iostream>
#include <typeinfo>

void CopyObject(const char* Original)
{
	if (nullptr == Original)
	{
		// �μ��� ���޵� ��ü�� NULL �̶�� ���ܸ� �߻���Ų��.

		throw std::runtime_error("�μ��� NULL�̴�.");
	}

	std::cout << Original << std::endl;
}

void MyFunc(char* Name) noexcept
{
	bool Ok = noexcept(CopyObject(Name));
	std::cout << std::boolalpha << "CopyObject() noexcept?" << Ok << std::endl;

	//if(Ok)
	CopyObject(Name);
}

int main()
{
	char* Name = nullptr;

	try
	{
		MyFunc(Name);
	}
	catch (int e)
	{
		std::cerr << e << std::endl;
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (std::exception& e)
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

