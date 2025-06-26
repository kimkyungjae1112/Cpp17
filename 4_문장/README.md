# 문장 04

- 네임스페이스 4.01
- 선언문과 정의문 4.02
- 식별자 적용 범위 4.03
- 범위 기반 for 문 4.04
- 예외 처리문 4.05
- 마무리 4.06

| 범주 | 내용 |
| --- | --- |
| 선언문 
또는 
정의문 | // 변수 선언
int a;
char c;

// 함수 선언
int func();

// 함수 정의
int func()
{
    //내용
} |
| 표현문 | 계산 작업을 나타내는 식

area = pi * (radius * radius)

* 계산된 작업 결과를 저장하지 않는다면, 계산 결과는 삭제되므로 계산 작업 자체가 무의미한 작업이 된다. |
| 조건문 | 조건문은 조건식에 따라 아래와 같이 서로 다른 작업을 수행한다. 조건문에서 사용하는 키워드는 if, else, switch, case 이다.

bool bCondition;
if(bCondition)
{
    // true 일 때 작업
}
else
{
    // false 일 때 작업
} |
| 반복문 | 반복문은 조건식의 충족 여하에 따라 아래 문장을 반복적으로 수행한다. 반복문을 가리키는 키워드는 do while, for, while이 있다.

for(int i = 0; i < 10; ++i)
{
    // 작업 10번 반복
} |
| 점프문 | 프로그램의 제어를 다른 문장으로 이동시키는 기능을 수행한다. 점프문을 가리키는 키워드는 break, continue, goto, return이다. 특수하게 return 키워드가 들어 있는 문장을 **반환문**이라고도 한다.

for(int i = 0; i < 10; ++i)
{
    if(i == 5)
        break;
} |
| 예외문 | 작업 실행 시 발생되는 예외는 정상적인 예외와 비 정상적인 예외로 나눌 수 있다. 그에 따라 적절하게 예외를 처리하는 문장이 필요하다. 예외 처리문을 가리키는 키워드는 throw, try-catch가 있다. |
| 레이블문 | goto문을 사용하여 다음 페이지와 같이 제어를 특정 위치로 이동시킬 때 해당 위치를 가리키는 문장을 말한다.
if(done) goto exit;

exit: // 레이블문이다.

클래스나 구조체에서 레이블문은 특정 위치를 가리키는 용도가 아닌 멤버에 대한 접근제어의 범위(public, private)를 나타내는 용도로 사용한다. |
| 디버그문 | 디버그를 수행할 때 자주 사용하는 매크로로 assert() : <cassert> 함수가 있다.

assert( 내용 );

assert() 함수에서 사용되는 인수(true 또는 false를 반환하는 식)는 항상 true가 되어야 한다. 만약 assert() 함수의 인수가 false가 된다면, 다음과 같이 에러를 발생시키고 추가 작업을 중단한다.

Assertion failed: expression, file filename, line line number

#define NDEBUG → 만약 더 이상 프로그램의 디버그 작업을 수행하지 않는다면, 다음과 같이 문장 하나를 추가 선언하면 된다. |
| 특수문 | 특수 목적을 위해 사용하는 문장이 존재한다. 예를 들어 하나 이상의 스레드 환경에서 다른 스레드가 특정 리소스의 접근을 제한하기 위해 아래와 같이 뮤텍스 객체와 lock() 함수문을 사용한다.

for(int i = 0; i < 5; ++i)
{
    mtx.lock()

    // 다른 스레드 접근 제한 작업

    mtx.unlock()
} |

### 4 - 01 네임스페이스(namespace)

- 식별자의 정규화된 이름
    - 클래스와 같은 데이터 타입 그리고 함수 앞에 네임스페이스를 붙여서 구분하는 방식을 식별자의 “정규화된 이름”이라 한다.
    
    ```cpp
    std::vector<std::string> vec;
    std::cout << vec[1] << std::endl;
    ```
    

- using 선언문
    - using 이란 키워드를 이용하여 사용하고자 하는 데이터 타입을 사전에 선언할 수 있다.
    
    ```cpp
    #include <iostream>
    
    using std::cout; // 표준 라이브러리에서 제공하는 cout 변수의 사용을 선언한다.
    using std::endl;
    
    int main()
    {
    	cout << "Hi" << endl;
    	cout << "Hello" << endl;
    }
    
    using 선언문은 C++ 11 이후부터 별칭이란 이름으로 사용할 수 있다.
    
    using Identifier = long; 
    typedef long Identifier;
    using MyIntVector = std::vector<int, MyAlloc<int>>;
    ```
    

- using 지시문
    - 프로그램 내 모든 식별자는 별도 정규화된 이름을 사용하지 않더라도 식별자가 해당 네임스페이스에 속한 식별자라는 사실을 알려주는 목적으로 using 지시문을 사용한다.
    
    ```cpp
    #include <iostream>
    
    using namespace std;
    
    int main()
    {
    	cout << "Hello World" << endl;
    	cout << "Hi" << endl;
    }
    ```
    
    - 어느 정도 규모 있는 프로그램을 여러 그룹에서 공동으로 개발한다면, using 지시문을 사용하지 않는 것이 좋다.

- 별칭 네임스페이스
    - 네임스페이스의 이름이 긴 경우나 여러 개의 네임스페이스가 연결하여 사용하는 경우 별칭을 사용해 별도 네임스페이스를 만들어 사용할 수 있다.
    
    ```cpp
    namespace Foo
    {
    	namespace Bar
    	{
    		namespace Baz
    		{
    			int Qux = 42;
    		}
    	}
    }
    
    namespace Fbz = Foo::Bar::Baz;
    
    int main()
    {
    	std::cout << Foo::Bar::Baz::Qux << std::endl;
    	std::cout << Fbz::Qux << std::endl;
    }
    ```
    

- 인라인 내부 네임스페이스
    - inline 네임스페이스는 외부 네임스페이스와 내부 네임스페이스 사이의 구분없이 사용할 수 있다. lnline 네임스페이스는 원래 다음과 같이 버전을 관리하고 자 하는 목적으로 만들어짐
    
    ```cpp
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
    
    실행결과
    Display 함수 Version 3
    WhatsUp 함수 Version 3
    Display 함수 Version 1
    ```
    

- 무명 네임스페이스
    - 네임스페이스의 이름을 명시하지 않으면 컴파일러는 ‘무명 네임스페이스’라는 이름으로 네임스페이스의 이름을 할당한다.
    
    ```cpp
    #include <iostream>
    
    namespace
    {
    	void SampleMethod()
    	{
    		std::cout << "무명 네임스페이스 내 SampleMethod" << std::endl;
    	}
    }
    
    namespace Sample
    {
    	void SampleMethod()
    	{
    		::SampleMethod();
    		std::cout << "Sample 네임스페이스 내 SampleMethod" << std::endl;
    	}
    }
    
    int main()
    {
    	Sample::SampleMethod();
    	SampleMethod();
    	::SampleMethod();
    }
    
    실행결과
    무명 네임스페이스 내 SampleMethod
    Sample 네임스페이스 내 SampleMethod
    무명 네임스페이스 내 SampleMethod
    무명 네임스페이스 내 SampleMethod#
    ```
    

### 4 - 02 선언문과 정의문

```cpp
#ifndef  Door_hpp
#define Door_hpp
#include <string>

extern int MyGlobal; // 외부에 선언된 전역 변수를 사용할 때 extern 키워드를 사용한다.

// 선언문을 포함하는 네임스페이스를 지정한다.
namespace MyNamespace
{
	struct Door
	{
		void Open();
		void Close();
		void ShowState() const;

		void SetName(std::string Str);
		std::string GetName() const;

		void State(int I);

		int IState;
		std::string Name;
	};

	inline void Door::State(int I)
	{
		IState = I;
	}
}

#endif // ! Door_hpp
```

1. #define 지정자를 사용하여 프로그램 내부에서 같은 헤더 파일을 두 번 이상 호출되지 않도록 막는다.
2. 인라인과 상수 표현식 함수는 매크로와 유사한 성격을 가지므로 보통 헤더 파일에 넣어 관리하는 것이 일반적인 관행이다.
3. 헤더 파일 내부에서는 되도록 또다른 헤더 파일을 ‘#include’로 포함시키지 않는다.
    1. 사이클 참조를 막을 수 있다.
    2. 헤더 파일 내부에 또다른 헤더 파일을 사용하지 않는다면, 컴파일러가 파일을 오픈하고 분석하는 작업이 필요없게 되며, 그로 인해 프로그램을 컴파일하고 빌드하는 시간을 최소화시킬 수 있다.

```cpp
#include <stdio.h>
#include <iostream>
#include <string>
#include "4-04.h"

int MyGlobal = 0;

namespace MyNamespace
{
	const int OPEN = 1;
	const int CLOSE = 0;

	void Door::Open()
	{
		State(OPEN);
	}

	void Door::Close()
	{
		State(CLOSE);
	}

	void Door::ShowState() const
	{
		printf("현재 문의 상태 : ");
		std::cout << ((IState == OPEN) ? "OPEN" : "CLOSE") << std::endl;
	}

	void Door::SetName(std::string Str)
	{
		Name = Str;
	}

	std::string Door::GetName() const
	{
		return Name;
	}
}

int main()
{
	MyNamespace::Door D;

	D.Open();
	D.ShowState();
	
	MyGlobal = 1;
	std::cout << MyGlobal << std::endl;
	return 0;
}
```

### 4 - 03 식별자 적용 범위

### 4 - 05 예외 처리문

```cpp
try
{
	예외가 발생할 가능성이 있는 문장.
}
catch(<exceptionType> e) //else if 처럼 여러개 사용 가능
{
	예외가 발생 시 처리하는 문장.
}
```

```cpp
#include <stdexcept>
#include <iostream>

void CopyObject(const char* Original)
{
	if (nullptr == Original)
	{
		// 인수로 전달된 객체가 NULL 이라면 예외를 발생시킨다.

		throw -1;
	}

	std::cout << Original << std::endl;
}

int main()
{
	try
	{
		char* Name = nullptr;
		CopyObject(Name);
	}
	catch (int e)
	{
		std::cerr << e << std::endl;
	}

	std::cout << "프로그램 종료!" << std::endl;
	return 0;
}

실행결과
-1
프로그램 종료!
```

throw 키워드는 두가지 작업을 수행한다.

1. throw 뒤에 나오는 데이터를 임시 저장소에 복사하여 자신을 호출한 함수에 백그라운드로 전달한다.
2. throw 를 호출한다면, 모든 작업을 중단하고 return 키워드처럼 작업 제어를 호출한 함수에 넘긴다. 만약 호출한 함수에 try-catch 문이 없다면, 운영체제는 일종의 exit() 함수인 std::terminate() 함수를 호출하고 현재 실행되는 프로그램을 종료시킨다.

```cpp
#include <stdexcept>
#include <iostream>
#include <typeinfo>

void CopyObject(const char* Original)
{
	if (nullptr == Original)
	{
		// 인수로 전달된 객체가 NULL 이라면 예외를 발생시킨다.

		throw std::runtime_error("인수가 NULL이다.");
	}

	std::cout << Original << std::endl;
}

void MyFunc(char* Name) noexcept
{
	bool Ok = noexcept(CopyObject(Name));
	std::cout << std::boolalpha << "CopyObject() noexcept?" << Ok << std::endl;

	//if(Ok)
	CopyObject(Name);
}

int main()
{
	char* Name = nullptr;

	try
	{
		MyFunc(Name);
	}
	catch (int e)
	{
		std::cerr << e << std::endl;
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "모든 Exception 처리" << std::endl;
	}

	std::cout << "프로그램 종료!" << std::endl;
	return 0;
}
```

noexcept 지정자를 사용한다면 try-catch 문을 사용하더라도 예외가 발생한다면, 그대로 종료하게 됨

- 오버플로우와 언더플로우
    - C++언어는 다음 예처럼 변수에 직접 리터럴 값이나 상수를 입력한다면, 컴파일 과정에서 오버플로우 에러가 발생한다.
    
    ```cpp
    int i1 = 2147483647 + 10; // 프로그램 작성하고 컴파일 과정에서 에러가 발생한다.
    
    int i2 = 2147483647;
    int i3 = i2 + 10; // 에러가 발생하지 않는다.
    ```