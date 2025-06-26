#include <iostream>

class Complex
{
public:
	constexpr Complex(double r, double i) : dRealValue(r), dImaginary(i) {}
	constexpr double GetReal() const { return dRealValue; }
	constexpr double GetImag() const { return dImaginary; }

private:
	double dRealValue;
	double dImaginary;
};

constexpr Complex Comp(0.0, 1.0);

int main()
{
	double x = 1.0;

	// 1. �������� �μ��� ���ͷ��� ����Ͽ����Ƿ� ����� �����ϴ�.
	constexpr Complex Cx1(1.0, 0.9);

	// 2. constexpr �����ڷ� ������ �μ��� ����� �Ǿ�� �Ѵ�. ���� �������� �μ���
	//    ������ ����Ѵٸ� x ������ ���� �� �� �ִ��ϴ��� ������ �߻��Ѵ�.
	// constexpr Complex Cx1(x, 1);

	// 3. ���� Cx2 ������ constexpr �����ڷ� ����� ����� �ƴϱ� ������ ���ȴ�.
	const Complex Cx2(x, 1); // Ok

	// 4. Comp ������ constexpr �����ڷ� ����Ǿ� �����Ƿ� ���� ���� ���� ���
	//    ����̹Ƿ� ������ ���� ����� �ʱ�ȭ�ϴ� �� ���ȴ�.
	constexpr double XX = Comp.GetReal(); // Ok
	constexpr double ImagVal = Comp.GetImag(); // Ok
	double xd = Comp.GetReal(); // Ok

	// 5. ���ǥ�������� ����� �����ڴ� ���ͷ��� �νĵǹǷ� �Ϲ� ������ �����ϴ� ��
	//    ����ϴ��� ���� ������ ���� �ʴ´�.
	Complex Cx3(2.0, 4.6);
	
	// int a;
	// Complex Cx4(a, 4.0); ����!

	return 0;
}