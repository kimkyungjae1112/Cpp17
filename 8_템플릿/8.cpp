#include <iostream>

template<typename T1>
class String
{
	// �Ʒ��� ��� ���ø� �Լ��̴�.
	template<typename T2>
	T1 Compare(const T2& s);

};

template<typename T1> // Ŭ���� ���ø�
template<typename T2> // ��� �Լ� ���ø�
T1 String<T1>::Compare(const T2& s)
{

}