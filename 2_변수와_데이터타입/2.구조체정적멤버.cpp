#include <iostream>
using namespace std;

struct X
{
	static void f();
	static int n;
	int m;
};

void X::f()
{
	cout << "�ȳ��ϼ���! n ������ : " << n << std::endl;
}

int X::n = 10;

int main()
{
	X y = { 100 };
	X::n = 100;
	y.f(); X::f; //���ڴ� �ȵ��� �˾Ҵµ� �Ǵ±���

}