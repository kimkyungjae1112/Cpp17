#include <iostream>
#include <iomanip>
#include <locale>

//���ڸ� 'xx/xx/xxxx' �������� �ܼ� ȭ�鿡 ����Ѵ�.
void ShowData(int m, int d, int y)
{
	// 1. �Ʒ� ������ ���� ���� ä�� �� ���ٸ�, '0'���� ä���� �ǹ̷� ����Ѵ�.
	std::cout << std::setfill('0');

	// 2. setw(2)�� �������� ���� �� ���ڸ� ä�� �� �ִ� ũ��� �϶�� �ǹ��̴�.
	//	  setw(4)�� �������� ���� �� ���ڸ� ä�� �� �ִ� ũ��� �϶�� �ǹ��̴�.
	std::cout << std::setw(2) << m << '/'
		<< std::setw(2) << d << '/'
		<< std::setw(4) << y << std::endl;
	std::cout << std::endl;
}

int main()
{
	// �������� std::defaultfloat Ÿ������ ����Ѵ�.
	// std::defaultfloat Ÿ���� �Ҽ��� ���� 6�ڸ��� �ݿø��Ͽ� 5�ڸ��� ����Ѵ�.
	double f = 3.1415926535;
	std::cout << f << std::endl;

	double x = 800000.0 / 81.0;
	// 3. std::fixed�� �Ǽ��� ����� �� ���� �Ҽ��� �ڸ��� ����Ѵ�.
	// 4. std::setprecision(2)�� �Ҽ������� �ڸ��� 2�� �Ѵٴ� �ǹ̷� ����Ѵ�.
	std::cout << std::fixed << std::setprecision(2) << x << std::endl;
	x = 2.0 / 3.0;

	// std::setprecision(4)�� �Ҽ��� ���� �ڸ��� 4�� �Ѵٴ� �ǹ̷� ����Ѵ�.
	std::cout << std::fixed << std::setprecision(4) << x << std::endl;
	std::cout << std::endl;

	// ���� ���� �Լ��� ȣ���Ѵ�.
	ShowData(1, 1, 2019);

	unsigned long x0 = 64206;
	// 5. �Ʒ� std::showbace�� ���ڸ� ����� �� ������ ǥ���϶�� �ǹ̷� ����Ѵ�.
	//	8������ '0'���� 16������ '0x'�� ǥ���Ѵ�. ������� ���� �� 'std::noshowbase'�� ����Ѵ�.
	//	std::oct�� 8�������� ���ڸ� ǥ���Ѵ�. std::hex�� 16�������� ���ڸ� ǥ���Ѵ�.
	std::cout << x0 << std::showbase
		<< " 8������ \"" << std::oct << x0 << "\""
		<< " 16������ \"" << std::hex << x0 << "\"" << std::endl;
	std::cout << std::endl;
	return 0;
}