//������ �ִ� ������ Ÿ�԰� ������ ���� ������ Ÿ���� ����
#include <iostream>
using namespace std;

enum Color1
{
	RED,
	GREEN,
	BLUE
};

enum class Color2
{
	GREEN,
	YELLOW,
	RED
};

int main()
{
	Color1 BackGround = RED;
	Color1 ForeGround = Color1::BLUE;
	//Color1 Color = Color2::RED; ����

	cout << RED << GREEN << BLUE << endl;

	// Color2 ������ Ÿ���� �Ʒ��� ���� ������ �����Ѵ�.
	//Color2 Stop = RED; ����
	//Color2 Wait = YELLOW; ����
	Color2 Go = Color2::GREEN; 

	cout << static_cast<int>(Color2::RED) << static_cast<int>(Color2::GREEN) << static_cast<int>(Color2::YELLOW) << endl;
}