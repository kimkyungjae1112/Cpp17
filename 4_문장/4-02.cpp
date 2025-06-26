#include <iostream>

#define USE_INLINE 1

namespace AppVersion
{
	namespace Version1
	{
		void Display()
		{
			std::cout << "Display �Լ� Version 1" << std::endl;
		}
	}

	namespace Version2
	{
		void Display()
		{
			std::cout << "Display �Լ� Version 2" << std::endl;
		}
	}

#if USE_INLINE
	inline
#endif
	namespace Version3
	{
		void Display()
		{
			std::cout << "Display �Լ� Version 3" << std::endl;
		}
	}
	namespace Version3
	{
		void WhatsUp()
		{
			std::cout << "WhatsUp �Լ� Version 3" << std::endl;
		}
	}
}

int main()
{
	// inline Ű���尡 �����ϱ� ���ӽ����̽��� ������ �� �ֳ�?
	AppVersion::Display();
	AppVersion::WhatsUp();
	AppVersion::Version1::Display();

	return 0;
}

