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
	cout << "안녕하세요! n 변수는 : " << n << std::endl;
}

int X::n = 10;

int main()
{
	X y = { 100 };
	X::n = 100;
	y.f(); X::f; //전자는 안될줄 알았는데 되는구나

}