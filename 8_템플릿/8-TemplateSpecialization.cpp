#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

// Ŭ���� ���ø��� �����ϰų� �����Ѵ�.
template<typename T>
inline std::string Stringify(T const& x)
{
	std::ostringstream out;
	out << x;
	return out.str();
}

// �Ʒ��� ��ü ���ø� Ư��ȭ�� ���� ���ø� �Ű������� �������� �ʴ´�. �׸��� ���ø� �μ��� �����Ͽ�
// ���� ���ø� �Ű������� �� �ٸ� ������ �Լ� �����ε�ó�� ����Ѵ�.
template<>
inline std::string Stringify<bool>(bool const& x)
{
	std::ostringstream out;
	out << std::boolalpha << x;
	return out.str();
}

template<>
inline std::string Stringify<double>(double const& x)
{
	std::ostringstream out;
	const int Sigdigits = std::numeric_limits<double>::digits10;
	out << std::setprecision(Sigdigits) << x;
	return out.str();
}

int main()
{
	std::cout << Stringify<int>(100) << ", " << Stringify<bool>(true) << ", " <<
		Stringify<double>(23.65) << std::endl;
}