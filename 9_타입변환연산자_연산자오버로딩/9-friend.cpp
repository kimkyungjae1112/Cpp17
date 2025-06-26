#include <iostream>

class Ours;

class Friend
{
public:
	int Func1(Ours& b);

private:
	int Func2(Ours& b) {}
};

class Ours
{
public:
	Ours(int i) : _b(i) {}

private:
	int _b;

	friend class Friend;
};

int Friend::Func1(Ours& b) { return b._b; }

// friend�� �ƴ϶�� private �� ���� �Ұ���
// class�� �����ϸ� ���� ���¤�
int Friend::Func2(Ours& b) { return b._b; }


int main()
{
	Ours Our(1);

	Friend friend1;
	std::cout << friend1.Func1(Our) << std::endl;
}