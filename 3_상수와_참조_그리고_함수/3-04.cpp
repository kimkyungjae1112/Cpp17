#include <iostream>
#include <string>
using namespace std;

int general(int i) { return i >= 0 ? i : -i; }

//C���� �����ϴ� ��ũ�� �Լ��̴�.
#define unsafe(i) ( (i) >= 0 ? (i) : -(i))

//�ζ��� �Լ��̴�.
inline int safe(int i) { return i >= 0 ? i : -i; }

//���ǥ�����̴�.
constexpr int expr(int i){ return i >= 0 ? i : -i; }

int main()
{
	int ans, x = 0;

	// 1. �ζ��� �Լ��� ������ ������ ����� �����Ѵ�.
	ans = (x >= 0) ? x : -x;
	cout << "ans = " << ans << ", " << x << endl;

	// 2. �Ϲ� �Լ��� ȣ���Ͽ� �����Ų ���̴�.
	x = 0;
	ans = general(x++);
	cout << "general(x++) = " << ans << ", " << x << endl;

	// 3. C����� ��ũ�θ� �����Ų ���̴�.
	x = 0;
	ans = unsafe(x++);
	cout << "unsafe(x++) = " << ans << ", " << x << endl;

	// 4. �ζ��� �Լ��� �����Ų ���̴�.
	x = 0;
	ans = safe(x++);
	cout << "safe(x++) = " << ans << ", " << x << endl;

	// 5. ���ǥ������ �����Ų ���̴�.������ ������ �Լ��� �μ��� 0�� �ԷµǴ�
	//    ����� �˱� ������ ������ ������ ��ȯ�Ǵ� ���� ����� ���Ǿ� ó���ȴ�.
	x = 0;
	ans = expr(x++);
	cout << "expr(x++) = " << ans << ", " << x << endl;
	return 0;
}