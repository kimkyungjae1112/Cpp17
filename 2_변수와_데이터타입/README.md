# 변수와 데이터 타입 02

- 변수(Variables)
- 데이터 타입(Data Type)
- char 타입과 wchar_t 타입
- 묶음 타입(구조체와 공용체)
- 열거형 타입(Enumerated Type)
- 변수의 초기화
- 마무리

## 2 - 01 변수

**저장 지정자(storage class specifier)** : 변수 내부의 데이터를 읽고 쓰는 방법을 명시하는 지정자

- volatile 지정자 : CPU 내 캐시에 저장된 변수의 데이터가 존재하더라도 무시하고 메인 메모리 내 변수로부터 데이터를 직접 읽고 쓰게 된다.
- static 지정자 : 변수가 함수나 클래스 내부에 존재하더라도 지역 변수가 아닌 전역 변수처럼 사용이 가능한 변수를 말한다. 이러한 변수를 정적 변수라 한다.

전역 변수와 정적 변수는 프로그램의 실행을 위해 메모리에 로드되는 순간에 변수가 생성되고 기본 값으로 초기화된다. 이를 **함축적인 초기화(implicit initialization)**라고 한다.

주의 사항

```cpp
#include <iostream>

void Test()
{
	static int var;
	++var;

	std::cout << var << std::endl;
}

int main()
{
	Test();
	Test();
	//int a = var; 에러 발생

	return 0;
}

// 함수 내부에 선언된 정적 변수는 마치 함수 외부에 선언된 전역 변수처럼 사용된다.
// 하지만 함수 내부에 설정된 정적 변수는 전역 변수처럼 사용하더라도 함수 외부에서 호출될 수 없다.
```

**extern 지정자** : 외부 프로그램에 의해 제작되고 컴파일된 실행 모듈이나 라이브러리 내 존재하는 **전역 변수**를 말한다.

```cpp
// 아래 x 변수는 extern "C++" int x 와 동일하며, 외부 모듈의 저장소를 가진
// C++ 언어로 제작된 변수라는 사실을 알려준다.
extern int x;

// 아래 y 변수는 C 언어로 제작된 외부 모듈 내 변수임을 선언한다.
// 아래 변수는 extern "C" {extern int y; } 와 동일하다.
extern "C" int y;

// 아래 변수는 프로그램 내부에서 선언된 변수로 역으로 외부에서 사용할 수
// 있음을 의미한다.
extern "C" { int z; }
```

**auto 타입**과 **decltype 타입**

```cpp
// name은 문자열을 저장하므로 초기화하는 과정에서 const char* 타입으로 인식된다.
auto name = "Seoul";
int foo = 0;
auto bar = foo; // bar 변수는 foo 변수의 데이터 타입(정수)으로 인식된다.

또는

decltype(foo) bar; // bar 변수는 위의 foo 변수의 타입과 같은 정수 타입으로 인식한다.
```

## 2 - 02 데이터 타입

변수 선언에 있어 가장 중요한 것이 변수 타입이라고 하는 데이터 타입이다. 사실 모든 변수를 비롯하여 함수에서 사용하는 인수와 함수에서 반환되는 값 모두 최종 확정된 데이터 타입이 있어야 컴파일할 수 있으며, 또한 컴파일러는 모든 식이나 함수를 컴파일하기 전에 암시적으로 적용할 데이터 타입을 지정한다.

데이터 타입은 함수 작업에 대한 결과값을 반환하기 위한 임의의 저장소에 할당되는 메모리의 크기를 결정하는 기준이 되며, 동시에 변수에 저장되는 데이터의 형태와 데이터를 해석하는 방법 및 데이터를 처리하는 작업 내용을 지정할 수 있게 만드는 기본이 된다.

리눅스는 디폴트로 **UTF-8** 이라 하는 유니코드를 사용한다.

- UTF-8 에서 한글은 초성,중성,종성으로 나누어 모두 3바이트(이를 **조합형**이라 한다)로 환산된다.

윈도우는 한글을 **CP949** 라고 하는 유니코드를 사용한다.

- CP949에서 한글은 2바이트(이를 **완성형**이라 한다)로 처리한다.

UTF-8의 장점은 언어 매핑 테이블이 없더라도 한글이나 한자 모두 표현이 가능하다. 그에 따라 HTTP처럼 다양한 언어를 지원하는 앱들은 UTF-8를 기본으로 사용한다.

반면에 윈도우는 한글을 표현할 때 EUC-KR 또는 CP949를 사용한다. EUC-KR 방식은 완성형 방식으로, 한글을 2바이트의 문자 집합(Character Set)으로 표현한다.

## 2 - 04 묶음 타입

구조체는 다음과 같이 static 지정자로 선언된 정적 멤버와 일반 멤버 모두를 가질 수 있다.

```cpp
struct X
{
	static void f();
	static int n;
	int m;
}

void X::f()
{
	std::cout << "안녕하세요! N  변수는 " << n << std::endl;
}
int X::n = 10;
```

구조체 내 정적 멤버는 다음과 같은 방법으로 접근하거나 호출할 수 있다.

- 구조체 내 정적 멤버는 선언 즉시 저장소를 할당받는다. 따라서 별도 구조체 타입의 변수의 선언없이 구조체의 이름과 범위 확인 연산자(’::’) 그리고 멤버 이름을 사용하여 정적 멤버를 호출할 수 있다.
    
    ```cpp
    X::f(); //함수 호출이 가능하다.
    X::n = 100; //멤버 변수의 초기화가 가능하다.
    ```
    
- 구조체 타입의 변수를 선언 하였다면, 아래와 같이 선언된 변수와 멤버 선택 연산자(’.’) 또는 멤버 선택 연산자(’→’) 그리고 멤버 이름을 서로 연결하여 호출할 수 있다.

공유체(union 타입)

공유체는 하나의 메모리 저장소를 여러 개의 데이터 타입을 가진 멤버들이 공유한다.

```cpp
#include <iostream>
#include <cstring>

union DataValue01 //공용체를 만든다.
{
	int Vint;
	float Vfloat;
	char Vstring[4];
};

struct DataValue02 //구조체를 만든다.
{
	int Vint;
	float Vfloat;
	char Vstring[4];
};

int main()
{
	std::cout << "공용체의 크기 = " << sizeof(DataValue01) << std::endl;
	std::cout << "구조체의 크기 = " << sizeof(DataValue02) << std::endl;
}
```

```cpp
#pragma warning(disable : 4996) //윈도우라면 이 문장을 추가시켜 준다.
#include <iostream>
#include <cstring>

// 데이터 타입별 상수를 선언한다.
#define None 1
#define Integer 2
#define Float 3
#define String 4

// 같은 메모리 영역을 정수와 실수 그리고 문자열로 공유한다.
union DataValue
{
	int Vint;
	float Vfloat;
	char* Vstring;
};

struct DataNode
{
	//콘솔 화면에서 받는 문자의 데이터 타입을 넣는 변수이다.
	int Type;
	DataValue Value;

	// ReadSomeInput() 함수는 콘솔로 입력되는 문자를 받아 정수 또는 실수 그리고 문자열에 따라 아래 Type변수와 Value 변수에 데이터를 입력시켜 주는 기능을 하는 함수이다.
	void ReadSomeInput()
	{
		char* p;

		//입력 문자를 받는데 있어 최대 크기를 100으로 잡았다. 더 좋은 방법은
		//"std::string s;" 처럼 char 타입이 아닌 std::string 타입으로 잡는게 좋다.
		char s[100];
		std::cout << "문자나 정수 그리고 실수 입력을 부탁합니다.";
		std::cin >> s;

		//입력된 문자가 정수인지 확인한다.
		long l = strtol(s, &p, 10);
		if (*p == 0) //반환하는 char 타입의 위치가 NULL이면 입력된 문자가 정수임을 나타낸다.
		{
			Type = Integer;
			Value.Vint = 1;
			return;
		}

		//입력된 문자가 실수인지 확인한다.
		float f = strtof(s, &p);
		if (*p == 0)
		{
			Type = Float;
			Value.Vfloat = f;
			return;
		}

		//이도저도 아니라면 문자열로 처리한다.
		Type = String;

		//\0를 추가하기 위해 한바이트를 늘린다.
		rsize_t len = strlen(s) + 1;
		Value.Vstring = (char*)malloc(len);
		strcpy(Value.Vstring, s);
	}

	//문자열은 malloc() 함수를 호출하여 힙 메모리를 할당받았기 때문에 필요하다면
	//다음과 같이 삭제시켜 주어야 한다.
	void FreeString()
	{
		if (String == Type)
		{
			free(Value.Vstring);
		}
	}
};

int main()
{
	DataNode InputData; // DataNode 공유체 타입의 변수를 선언한다.
	InputData.ReadSomeInput();

	//타입에 따라 선택하여 데이터를 출력한다.
	switch (InputData.Type)
	{
	case Integer:
		std::cout << "Integer : " << InputData.Value.Vint << std::endl;
		break;
	case Float:
		std::cout << "Float : " << InputData.Value.Vfloat << std::endl;
		break;
	case String:
		std::cout << "String : " << InputData.Value.Vstring << std::endl;
		break;
	}

	//작업 완료후에 만약 문자열을 할당받았다면 다음과 같이 해제시켜주어야 한다.
	InputData.FreeString();
}
```

`strtol(const char* str, char** str_end, int base) : <cstdlib>`

첫번째 인수로부터 문자열을 읽는다. 만약 정수의 문자열이라면, 정수 문자열을 추려내어 정수로 만들어 반환한다.

두번째 인수는 정수로 변환하지 못한 문자열의 위치를 가리킨다.

세번째 인수는 10진법인지 16진법인지 구분한다.

`strtof(const char* str, char** str_end) : <cstdlib>`

위와 동일

## 2 - 06 변수의 생성과 초기화

C++ 언어에는 변수를 선언하고 동시에 초기화시키는 다양한 방법이 존재한다.

아래는 원시형 변수를 초기화하는 방법이다.

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	// 1. 대입 연산자('=')을 사용하여 상수를 대입하는 방식으로 변수를 초기화한다.
	// 이는 C 언어에서 사용하는 대표적인 초기화 방법이다.
	int a = 10;
	cout << "a : " << a << endl;

	// 2. 객체 지향 언어에서 객체를 생성시킬 때 사용하는 생성자처럼 변수와
	// '()' 함수 호출 연산자 그리고 리터럴을 인수로 사용하여 변수를 초기화한다.
	int b(20);
	std::cout << "b : " << b << std::endl;

	// 3. 중괄호를 사용하여 변수를 초기화한다.
	int c{ 30 }; //-std=c++11 이후부터 사용이 가능하다.
	std::cout << "c : " << c << std::endl;

	// 4. int 타입의 무명 변수를 생성하고 무명 변수의 값을 변수에 대입시켜 초기화한다.
	// int(40)과 같이 이름이 없는 무명 변수는 문장이 완료되면 자동 삭제된다.
	int d = int(40); //int(40)은 변수의 이름이 없는 무명 변수이다.
	std::cout << "d : " << d << std::endl;

	// 5. 변수 생성 시 비어 있는 인수로 변수를 초기화 한다면 플랫폼에 따라
	// 컴파일이 될 수도, 안될 수도 있다. 
	// 해당 초기화는 변수에 어떤 값이 들어있는지 알 수 없다.
	int e(); // 'int e();' 의 초기화 작업은 원칙적으로 허용되지 않는다.

	// 6. 아래처럼 무명 변수를 선언하고 대입한다면, 변수는 0으로 초기화된다.
	// 이는 객체 지향 언어에서 유래된 방식이다.
	int f = int(); // 여기서 int() 함수를 디폴트 생성자라 부른다.

	// 7. 배열의 초기화처럼 중괄호와 함께 리터럴을 만들어 변수에 대입하여 생성한다.
	int g = { 50 };

	// 8. new 연산자를 사용하여 메모리 저장소를 생성하여 변수에 할당한다.
	int* h = new int; // new 라는 지시어를 사용한다면, 저장소는 heap 메모리에 저장된다.

	// 초기화없이 생성되면, 생성된 변수는 알 수 없는 값이 들어있게 된다.
	
	// 9. new 지정자와 () 함수 호출 연산자를 함께 사용한다면 포인터가 가리키는 저장소는
	// 자동으로 초기화된다. 이 방법은 앞에서 언급한 것처럼 객체 지향 언어에서 유래된 방식이다.
	int* i = new int();
	
	int* j = new int(60); //j 포인터가 가리키는 저장소의 값은 60으로 초기화된다.

	// 10. bool 타입의 변수는 true와 false를 사용하여 초기화된다.
	// 타입이 다르다 하더라도 초기화하는 방법은 앞에서 설명한 변수들과 동일하다.
	bool ok = true; //bool ok(false);
}
```

`‘int()’` 와 같은 무명 변수는 생성된 이후에 한번 사용하고 다시 삭제된다. 그에 따라 컴파일러는 최적화시키는 방법으로 무명 변수를 대신하여 `‘int f(10)’` 처럼 **실제 변수를 생성하고 초기화 시키는 것이 좋다.** 

변수는 선언과 동시에 초기화하는 것이 좋다.

아래와 같이 동적 배열도 `‘()’` 함수 호출 연산자를 이용해 선언과 동시에 초기화 할 수 있다.

```cpp
char* pch = new char[BUFFER_SIZE]();
```

선언과 동시에 초기화 할 수 없는 경우 **‘초기화한다’는 의미로 중괄호를 사용하여 지역 범위를 만들어 사용한다.**

```cpp
vector<int> v; // vector 클래스의 v 변수를 선언한다.
{ //아래와 같은 방법으로 초기화시킨다.
	v.push_back(1);
	v.push_back(2);
}
```

묶음 타입의 초기화 시 주의사항

```cpp
#include <iostream>
#include <cstdio>

struct Data
{
	int age; //나이
	char name[100]; //이름
	int balance; //지갑 속의 용돈
};

struct Test
{
	Test(int a) {}
};

void Print(Data user)
{
	std::cout << user.age << ", " << user.name << ", 잔액 : " << user.balance << std::endl;
}

int main()
{
	// 1. 대입 연산자를 사용하여 리터럴을 대입하는 방식으로 변수의 생성과 초기화는 구조체나 클래스 타입의 경우 허용하지 않는다.
	// 컴파일 시 int 타입에서 구조체로 타입을 변환시킬 수 없다는 에러가 발생한다.
	// Data user01 = 21;
	// 이것은 내 생각 -> 위의 구절은 인자가 하나인 생성자를 염두에 두지 않고 선생님께서 쓰신 말같다.
	Test test = 1;

	// 2. 구조체 내 변수의 순서에 맞추어 리터럴을 함수의 인수로 사용하여 변수를 초기화한다면,
	// 다음과 같은 에러가 발생한다. 이 문제의 해결 방안은 구조체의 생성자를 만들어 제공하면 된다.
	// Data user02(33, "이순신", 200000);

	// 3. 그러나 아래와 같이 중괄호를 사용한다면, 초기화가 혀용된다.
	// 입력된 인수는 순서적으로 멤버 변수에 할당된다.
	Data user03{ 53, "강감찬", 20000 }; // -std=c+11 이후부터 사용이 가능하다.
	Print(user03);

	// 4. 무명 변수를 만들어 무명 변수의 값을 변수에 대입시켜 초기화한다. 앞에서 보았던 2. 와 동일한 
	// 에러가 발생한다. 이 문제 역시 생성자를 만들어주면 해결된다.
	// Data user04 = Data(45, "이성계", 304040);

	// 5. 아래처럼 함수 호출 연산자와 함께 변수를 생성한다면, 컴파일 에러가 발생한다.
	// 무명변수는 허용되지만 안정성의 이유로 아래와 같이 직접 변수를 생성하는 방식은 ISO에서 금지하는 방식이다.
	// Data user05();

	// 6. 아래와 같이 Data 타입의 무명 변수를 생성하고 변수에 대입한다면, 변수가 생성되는
	// 동시에 모든 멤버 변수는 타입에 따라 초기화된다.
	Data user06 = Data();
	Print(user06);

	// 7. 구조체와 클래스는 다음과 같이 나열된 값으로 변수에 순서대로 할당하여 초기화시킬 수 있다.
	// 이 방식은 C 언어에서 유래된 방식이다.
	Data user07 = { 21, "홍길동", 10000 };
	Print(user07);

	// 8. 초기화없이 구조체의 변수를 선언한다면 멤버 변수에 알 수 없는 값이 들어간다.
	Data user08;
	Print(user08);

	// new 라는 키워드를 사용하여 메모리 저장소를 생성하여 변수에 할당한다.
	// 이 경우 역시 멤버 변수에 알 수 없는 값이 들어간다.
	Data* user_08 = new Data;
	Print(*user_08);

	// 9. new 지정자와 함께 아래처럼 변수를 생성하면 모두 자동으로 초기화된다.
	Data* user09 = new Data();
	Print(*user09);
}
```

```cpp
#pragma warning(disable : 4996) //윈도우라면 이 문장을 추가시켜 준다.
#include <iostream>
#include <cstdio>
#include <cstring>

struct Data
{
	// 아래와 같이 사용자 정의 생성자를 정의한다.
	Data(int a, const char* n, int b)
	{
		age = a;
		strcpy(name, n);
		balance = b;
	}

	//컴파일러는 기본으로 아래와 같은 디폴트 생성자를 자동 제공해준다.
	Data()
	{
		age = 0;
		memset(name, 0, 100);
		balance = 0;
	}

	int age; //나이
	char name[100]; //이름
	int balance; //지갑 속의 용돈
};

struct Test
{
	//Test() {}
	int a;
};

void Print(Data user)
{
	std::cout << user.age << ", " << user.name << ", 잔액 : " << user.balance << std::endl;
}

void Print(Test test)
{
	std::cout << test.a << std::endl;
}

int main()
{
	Data user02(33, "이순신", 2000);
	Data user04 = Data(45, "이성계", 3000);
	Data* user05 = new Data(60, "연개소문", 45000);
	Data user08;
	Data* user_08 = new Data;

	Print(user02);
	Print(user04);
	Print(*user05);
	Print(user08);
	Print(*user_08);
	
	Test test; //명시적으로 생성자를 만들어주지 않으면 해당 변수는 사용할 수 없음
	Print(test);
}
```

<aside>
💡

알게된 점

</aside>

컴파일러가 만들어준 디폴트 생성자만 가지고선 일반적으로 변수를 생성해서 사용할 수 없다. 프로그래머가 생성자를 만들어주면 변수로 사용 가능하며, 거기서 멤버 변수를 초기화 해주면 a가 쓰레기 값이 아닌 정상적인 값이 출력되게 된다.