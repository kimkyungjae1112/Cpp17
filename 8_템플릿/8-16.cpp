#include <iostream>

static int i = 0;

template<typename T>
void ParamCheck(T&& s)
{
	// is_reference 클래스 템플릿은 s의 데이터 타입이 참조라면 value 변수를 true로 반환한다.
	if (std::is_reference<T&&>::value)
	{
		// T&&가 lvalue 참조라면 value 상수는 true를 반환한다.
		if (std::is_lvalue_reference<T&&>::value)
		{
			// 타입이 상수 타입이라면 동일하게 value는 true를 반환한다.
			if (std::is_const<T&&>::value)
			{
				std::cout << ++i << ". " << s << " 인수는 'const T&' 타입이다.\n";
			}
			else
			{
				std::cout << ++i << ". " << s << " 인수는 'T&' 타입이다.\n";
			}
		}
		else
		{
			std::cout << ++i << ". " << s << " 인수는 'T&&' 타입이다.\n";
		}
	}
	else
	{
		std::cout << ++i << ". " << s << " 인수는 'T' 타입이다.\n";
	}
}

int main()
{
	// 1. (char[5]) 타입의 저장소를 생성하여 전달되므로 'T&' 타입으로 인식된다.
	ParamCheck("리터럴");

	// 2. 임시 저장소를 생성한다. 임시 저장소는 'T&&' 타입으로 인식된다.
	ParamCheck(std::string{ "무명변수" });

	// 3. s3 변수는 빠른 처리를 위해 'T&' 타입으로 처리한다.
	std::string s3{ "일반 변수" };
	ParamCheck(s3);

	// 4. const 지정자를 사용하여 lvalue 참조를 상수로 만든다면, 'T&' 타입으로 처리한다.
	const std::string& s4{ "const 상수" };
	ParamCheck(s4);
	
	// 5. 참조에 대해 move() 함수를 사용한다면 'T&&' 타입으로 인식된다.
	std::string ss = std::string("std::move(") + s3 + std::string(")");
	std::string& s5{ ss };

	// 6. rvalue 참조 타입으로 선언하였지만 실제 일반 변수로 등록된다. 따라서
	// 인수는 'T&'으로 전달된다.
	std::string&& s6 = std::string("대입연산자와 무명변수");
	ParamCheck(s6);

	std::cout << std::endl;
	return 0;
}