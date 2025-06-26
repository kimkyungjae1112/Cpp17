#include <iostream>
#include <vector>

int main()
{
	int N = 100;
	void* NV = &N; // �Ͻ��� ��ȯ �۾��� ����

	// long Ÿ���� �����Ͱ� ���� Ÿ���� ������ ����Ű���� �����.
	long* N01 = static_cast<long*>(NV);
	int* N02 = static_cast<int*>(&N);

	// ���� ������ ����Ͽ� �����͸� ��½�Ų��.
	std::cout << "N = " << N << ", *N01 = " << *N01 <<
		" , *N02 = " << *N02 << '\n';

	std::vector<long> E = { 1,23,10 };
	void* VoidP = &E; // void Ÿ���� �����͸� �����ϰ� �����̳� ��ü�� �ּҸ� ����

	// �����̳� ��ü�� �����ϴ� ����� Ÿ���� long Ÿ�Կ��� int Ÿ������ �ٲ�
	std::vector<int>* Vec = static_cast<std::vector<int>*>(VoidP);

	// �� �ٸ� �����̳� ��ü�� �����͸� ���� ����
	std::vector<int> Vr = *Vec;
	for (int a : Vr)
	{
		std::cout << a << " "; 
	}
	std::cout << std::endl;
}