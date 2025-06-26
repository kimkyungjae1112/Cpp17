# 연산자와 람다 05

- 연산자
- 단항 연산자
- 이항 연산자
- 기타 연산자
- new와 delete 연산자
- lvalue와 rvalue의 기본 개념
- 람다
- 마무리

연산자 역시 넓은 의미의 함수에 포함된다.

### 5 - 01 연산자

- 연산자의 우선 순위와 결합 방향을 항상 생각하자.

### 5 - 02 단항 연산자

- ++, — 증감 단항 연산자
    - 내부 구현

```cpp
* 전위 증감 단항 연산자 
int operator++()
{
	(*this) += 1;
	return *this;
}

* 후위 증감 단항 연산자
int operator++(int)
{
	int Temp = *this;
	++(*this);
	return Temp;
}

내부 구현의 예시로 후위 증감 연산자의 경우에는 원래 변수(객체)의 데이터를 반환한 후
연산 작업을 수행한다.

전위 증감 연산자의 경우 연산 작업 수행 후 연산된 데이터를 반환한다.

후위 증감 연산자는 전위 증감 연산자보다 최소 하나내지 두 개의 작업 단계를 거친다.
```

- ~ 비트 전환 연산자
    - 실수 타입이 아닌 정수 타입이나 char 타입의 변수에서 사용하며, 해당 변수의 비트를 1의 보수로 변경한다.
    - 이때 연산 작업은 사전에 항상 데이터 타입 변환 작업이 먼저 이루어진다.

ex) 언리얼에서 `uint8 변수명 : 1`  이런 식으로 변수를 선언한 적이 있었다. 이때 값을 반대로 바꾸기 위해서  `!` 연산자를 사용했었는데 오류가 났었고,  `~` 연산자를 사용해 반대로 바꾸곤 했다.

- 모든 연산 작업은 선행 작업으로 데이터 타입 변환 작업이 포함되어 있다.
    - int 타입, long 타입이 아닌 다른 데이터 타입을 변수의 데이터 타입으로 사용한다면, 항상 타입 변환이란 작업이 이루어진다.
    - 타입 변환 작업은 모든 프로그램 내 연산 작업에 있어 공통적으로 이루어지는 선행 작업이다.

### 5 - 03 이항 연산자

- 산술 연산을 수행하기 전 먼저 컴파일러가 정해진 레지스터의 변수 타입으로 변수와 리터럴을 변형시키는 작업을 수행한다.
- 실제 연산 작업의 수행 주체가 데이터가 저장된 메모리가 아닌 CPU 내 레지스터이기 때문에 레지스터가 지원하는 타입에 맞추어 자동으로 변환이 이루어지게 된다.
    - 해당 과정을 타입 프로모션, 타입 변환이라 불리며 우리가 일반적으로 생각하는 타입 변환 ex)
    
    ```cpp
    char a = 1;
    int b = (int)a; //c타입의 캐스팅
    ```
    
    - 이러한 것과는 조금 다르게 산술 연산자를 통해 연산을 진행할 때 두 수를 레지스터에 집어넣게 되는데 이때 레지스터의 타입에 맞게 데이터 타입을 변환한다는 것 같다. → 내 생각

- 정리
    - 연산자를 기준으로 변수의 데이터 타입이 레지스터의 데이터 타입과 다르다면, 가장 먼저 타입 변환 작업이 이루어진다. 예를 들어 `short` 타입은 `int` 타입으로 타입 변환이 이루어진다.
    - 연산 작업을 수행한다.
    - 연산 작업 결과 역시 이항 연산에서 사용한 변수(또는 피연산자)의 타입으로 타입 변환이 이루어진다.

### 5 - 05 new와 delete 연산자

```cpp
new (argument list)(optional) (type) initializer(optional)
new (argument list)(optional) type initializer(optional)
```

- argument list : 기존 사용한 메모리나 new에 대한 설정 옵션 등을 가리킨다.
- type : 데이터 타입을 가리킨다.
- initializer : 저장소에 입력되는 초기화 값을 가리킨다. 초기화 값은 ‘{}’ 중괄호를 사용하거나 ‘()’ 소괄호를 사용하여 표기한다.

- malloc
    - 메모리를 할당하는 `함수`
    - 생성자를 호출하지 않음
- new
    - 새로운 메모리를 할당 및 객체 class를 생성하는 `연산자`
    - 생성자 호출
        - 생성자의 역할은 부모 클래스의 생성자 호출
        - 멤버 객체의 생성자 호출
        - vtable 초기화 ( 생성자가 호출되며 초기화, 불리지 않으면 virtual 사용 불가능 )

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>

struct Account
{
	char* AccountNum;
	char* Name;
	int Balance;

	void Print()
	{
		printf("계좌 : %s, 소유자 : %s", AccountNum, Name);
		printf(", 잔액 : %i\n", Balance);
	}

	void Deposit(int Money)
	{
		Balance += Money;
	}

	void WithDraw(int Money)
	{
		Balance -= Money;
	}
};

Account* OpenAcct(const char* Id, const char* Name, int Bal)
{
	Account* Temp = new(std::nothrow) Account();
	if (Temp == nullptr) return nullptr;

	//문자열 크기와 마지막에 '\0'를 포함해야 하므로 strlen() 함수가 반환되는 값에
	//1을 추가해줘야 한다.
	char* NewId = new(std::nothrow) char[strlen(Id) + 1];
	if (NewId == nullptr) return nullptr;

	strcpy(NewId, Id);
	Temp->AccountNum = NewId;

	char* NewName = new(std::nothrow) char[strlen(Name) + 1];
	if (NewName == nullptr) return nullptr;

	strcpy(NewName, Name);
	Temp->Name = NewName;
	Temp->Balance = Bal;
	std::cout << "Account 객체를 생성하였습니다." << std::endl;
	return Temp;
}

int CloseAcct(Account* Acct)
{
	std::cout << "Account 객체를 삭제하였습니다." << std::endl;

	delete[] Acct->AccountNum;
	delete[] Acct->Name;
	delete Acct;
	return 1;
}

int main()
{
	Account* Hong = OpenAcct("120-345-12909", "홍길동", 60000);
	if (Hong == nullptr) return -1;

	Account* Kim = OpenAcct("129-345-929100", "김홍도", 0);
	if (Kim == nullptr) return -1;

	// 홍길동의 계좌에서 돈을 빼서 김홍도의 계좌로 이체한다.
	Hong->WithDraw(2000);
	Kim->Deposit(2000);
	Hong->Print();
	Kim->Print();

	CloseAcct(Hong);
	CloseAcct(Kim);

	return 0;
}
```

### 5 - 06 lvalue와 rvalue의 기본 개념

- lvalue, glvalue, xvalue, rvalue, prvalue

- lvalue (left-hand side value)
    - lvalue는 역사적으로 대입 연산자의 왼쪽 위치에 놓이는 변수를 말한다. lvalue는 변수이외에 함수나 연산자를 포함한다.
    - 식별 가능한 아이덴티티를 가지고 있다.
    - lvalue로 언급되는 변수와 함수는 자체적으로 데이터를 이동하거나 또는 복사하는 작업을 수행하지 않는다.
- rvalue (right-hand side value)
    - rvalue는 역사적으로 대입 연산자의 오른쪽 위치에 놓이는 리터럴이나 임시 저장소, 무명 변수 그리고 일반 데이터를 반환하는 함수를 rvalue라고 말한다.
    - rvalue의 공통적인 특징은 데이터의 이동이나 복사가 존재한다.

- prvalue (pure rvalue)
    - prvalue : 순수한 rvalue는 아이덴티티를 가지지 않으며, 또한 데이터의 이동이나 복사만이 가능하다.
    - prvalue의 주소는 얻을 수 없다.
    - lvalue로 사용할 수 없다.

- prvalue의 예
    - 리터럴(문자열 제외)
    - true, nullptr 처럼 특수 목적으로 사용하는 키워드
    - 참조나 포인터가 아닌 데이터를 반환하는 람다
    - 연산 작업의 결과는 임시 저장소에 보관되며 prvalue가 된다.
    - 후위 증감 단항 연산자

- xvalue (expiring value)
    - 삭제 예정값
    - 임시 저장소를 가리키나 아이덴티티의 속성을 부여할 수 있음
    - && 기호를 붙여 rvalue 참조 타입으로 표시한다.
    
    ```cpp
    int&& Addition(int a, int b)
    {
    	//std::move() 함수는 rvalue 참조를 만드는 기능을 제공한다.
    	return std::move(a+b);
    }
    ```
    
    - xvalue는 아이덴티티를 가지는 동시에 데이터의 복사와 이동이 이루어진다.

- xvalue 의 도입 이유
    - 프로그램의 성능 향상
    
    ```cpp
    ex) 임시 저장소 A, B는 임의로 명명한 이름
    
    int y = f(n) * 100 + (x + 2) % 5;
    
    1. f(n) 호출 -> n 변수에 대한 복사 (call bt value)가 이루어진다.
    2. f(n)의 반환값을 임시저장소 A에 넣는다.
    3. (x + 2) 연순 수행 -> 임시저장소 B에 넣는다.
    4. A 임시 저장소로부터 값을 읽어 100을 곱하고 다시 A에 넣는다.
    5. B 임시 저장소로부터 값을 읽어 5를 나누고 다시 B에 넣는다.
    6. A와 B 임시 저장소로부터 값을 읽고 합하여 다시 A 임시 저장소에 넣는다.
    7. A 임시 저장소로부터 값을 읽어 y 변수에 넣는다.
    8. 임시 저장소는 모든 작업을 마친 이후에 문장을 종료하는 시점에 모두 삭제된다.
    ```
    
    - 이러한 연산을 더욱 효율적으로 수행하기 위해 문장의 종료 시 즉시 삭제되던 임시 저장소의 소멸 시간을 다소 지연시킨 개념이 xvalue 이다.

### 5 - 07 람다

- C++ 에서 함수는 크게 두 개로 나뉜다
    - 일반 함수 : 우리가 일반적으로 아는 함수
    - 무명 함수 : 람다, 함수 객체처럼 함수의 이름 없이 사용이 가능한 함수

```cpp
ex) 람다 사용

#include <iostream>

int main()
{
	auto funa = [] { std::cout << "Hello 람다" << std::endl; };
	funa();
	
	auto funb = [](int n) { std::cout << "정수 : " << n << std::endl; };
	funb(333);
	return 0;
}
```

- 람다 포맷
    - [캡처절] { 본문 }
    - [캡처절](인수) { 본문 }
    - [캡처절](인수) → 반환 타입 { 본문 }
    - [캡처절](인수) mutable(옵션) constexpr(옵션) 예외 속성 → 반환 타입 { 본문 }

- 캡처절 (Capture Clause)
    - 람다가 선언된 위치를 기준으로 자신의 앞에 선언된 변수를 어떤 방식으로 사용할 것인지를 컴파일러에게 알려주는 기능
    - 캡처 디폴트, 캡처 리스트로 구분된다. 둘 다 사용할 경우 캡처 디폴트가 먼저 선행되야함
    - 캡처 디폴트
        - [&] 참조 캡처(by-referece capture) 전방 선언된 외부 변수 모두를 참조로 사용한다.
        - [=] 값 캡처(by-value capture) 전방 선언된 외부 변수의 값을 사용한다.
        - [   ] 아무 것도 캡처 안함 → 외부 변수 사용 안함

- 캡처 리스트
    - 앞에서 선언된 변수 가운데 사용할 변수를 개별적으로 어떻게 사용할 것인지 언급할 때 사용한다.
    
    ```cpp
    #include <iostream>
    
    struct S2
    {
    	void Func(int i);
    	int a;
    };
    
    void S2::Func(int i)
    {
    	[&] {}; // Ok : i 매개 변수에 대해 참조 캡처(캡처 디폴트)
    	[=] {}; // Ok : i 매개 변수에 대해 값 캡처(캡처 디폴트)
    	[&, i] {}; // Ok : i 변수를 제외하고 나머지 변수는 참조 캡처 사용
    	[=, &i] {}; // Ok : i 변수는 참조 캡처로 사용되고 나머지 모두는 값 캡처로 사용
    	//[&, &i] {}; Error : 참조로 사용하는 것 중복
    
    	[=, this] { this->a = i; }; //C++ 20 부터 this 캡처가 가능한데?
    }
    ```
    

- mutable 키워드(옵션)
    - 람다 캡처절에 선언된 변수들은 const로 인식됨, 따라서 람다에 mutable 이란 키워드를 본문 앞에 사용하여야만 의도적으로 참조의 수정이 가능해진다.
    
    ```cpp
    #include <iostream>
    
    int main()
    {
    	int m = 0;
    	int n = 0;
    
    	// 무명 람다 함수를 생성하는 동시에 () 함수 호출 연산자를 사용하여 실행시킨다.
    	[&, n](int a) mutable { m = (++n) + a; }(4);
    
    	// n은 값 인수(pass by value)로 람다 내부에서 수정되더라도 변화되지 않는다.
    	// 참조로 받은 캡처는 수정 가능
    	std::cout << m << ' ' << n << std::endl;
    
    	int a = 1, b = 1, c = 1;
    	[a, &b, &c]() mutable { a = 3; b = 3; c = 3; }();
    
    	std::cout << a << " " << b << " " << c << std::endl;
    }
    ```
    

- constexpr 지정자(옵션)
    - constexpr 지정자는 함수의 반환되는 값이 상수란 사실을 컴파일러에게 알려준다.
    
    ```cpp
    auto ID = [](int n) constexpr {return n;};
    constexpr int I = ID(3);
    ```
    

- throw() (옵션)
    - 람다 역시 함수이므로 다음과 같이 내부에서 예외를 발생시킬 수 있다.
    
    ```cpp
    try
    {
    	[]() { throw 5; }();
    }
    catch(int e)
    {
    	std::cout << e << '\n';
    }
    ```
    

```cpp
auto f = [](int x) throw() -> bool { return x % 3 == 0; };
auto h = []() throw() { return rand(); };
std::cout << f(2) << " " << h() << '\n';

try
{
	// 'lambda' : 함수는 예외를 Throw 하지 않도록 지정되어 있어 에러가 발생한다.
	[]() throw() { throw 5; }();
}
catch (int e)
{
	std::cout << e << '\n';
}
```

```cpp
#include <iostream>

int main()
{
	int a = 1, b = 1, c = 1;

	// 람다의 캡처절은 위의 변수들을 받아들인다.
	auto m1 = [a, &b, &c]() mutable
		{
			a = 3; b = 3; c = 3;
		};

	a = 2; b = 2; c = 2;

	// 람다를 선언하는 동시에 정의한다.
	auto m2 = [=]() mutable
		{
			a = 4; b = 4; c = 4;
		};

	m1();
	std::cout << a << ' ' << b << ' ' << c << '\n'; // 2 3 3 출력
}
```

```cpp
#include <cstdlib>
#include <iostream>

int main()
{
	int array[10];
	for (int i = 0; i < 10; ++i)
	{
		array[i] = std::rand() % 1000;
	}

	std::cout << "sort 전 : ";
	for (int i = 0; i < 10; ++i)
	{
		std::cout << array[i] << " ";
	} 
	std::cout << std::endl;

	// 아래 람다는 정렬에 따른 비교 함수로 사용한다. 
	// 데이터 타입 명시
	// 인수는 함수처럼 포인터를 람다에 전달할 때 사용된다.
	auto sorter = [](const void* first, const void* second) -> int
		{
			return (*(int*)first - *(int*)second);
		};

	qsort(array, 10, sizeof(int), sorter);
	
}
```