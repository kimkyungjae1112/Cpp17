#include <iostream>

#define USE_INLINE 1

namespace AppVersion
{
	namespace Version1
	{
		void Display()
		{
			std::cout << "Display 함수 Version 1" << std::endl;
		}
	}

	namespace Version2
	{
		void Display()
		{
			std::cout << "Display 함수 Version 2" << std::endl;
		}
	}

#if USE_INLINE
	inline
#endif
	namespace Version3
	{
		void Display()
		{
			std::cout << "Display 함수 Version 3" << std::endl;
		}
	}
	namespace Version3
	{
		void WhatsUp()
		{
			std::cout << "WhatsUp 함수 Version 3" << std::endl;
		}
	}
}

int main()
{
	// inline 키워드가 붙으니까 네임스페이스를 생략할 수 있네?
	AppVersion::Display();
	AppVersion::WhatsUp();
	AppVersion::Version1::Display();

	return 0;
}

