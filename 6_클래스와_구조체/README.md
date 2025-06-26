# 클래스와 구조체 06

- **객체 지향 프로그래밍**
    - 추상화
        - 사물을 추상화하고 속성과 기능을 분류하여 클래스를 만든다.
    - 캡슐화
        - 클래스 내부에서 여러가지 속성과 함수를 묶어서 외부에 노출하지 않음으로써 외부 프로그램의 수정을 최소화함을 의미한다.
    - 상속
        - 프로그램 코드의 재사용을 목적으로한다.
        - 코드 중복을 없앤다.
    - 다형성
        - 하나의 인터페이스 또는 하나의 상위 클래스를 통해 하위 클래스의 다양한 기능을 제공하는 것을 의미한다.

- 클래스의 포맷
- 접근 지정자
- 구조체와 클래스의 차이
- 객체의 초기화
- 클래스의 관계
- 클래스 상속
- 가상 함수
- 다중 상속의 문제점

### 6 - 01 클래스 포맷

```cpp
struct 구조체-이름 final(옵션) [ : 기본-구조체, ... ]  // []는 상속받을 구조체 의미
{
	멤버
}

class 구조체-이름 final(옵션) [ : 기본-클래스, ... ] // []는 상속받을 클래스 의미truct 구조체-이름 final(옵션) [ : 기본-구조체, ... ]  // []는 상속받을 구조체 의미{	멤버}
class 구조체-이름 final(옵션) [ : 기본-클래스, ... ] // []는 상속받을 클래스 의미
{
	멤버
}
```

```cpp
#include <iostream>
#include <algorithm>
#include <complex>

struct S
{
	static int a[];
	inline static int n = 1;
	const static int t = 1;
	const static int k;
	const static int m{ 2 };
	constexpr static int arr[] = { 1,2,3 };
	constexpr static std::complex<double> c = { 1,2 }; // 각각 실수와 허수로 들어간다.
};

// 아래는 위의 구조체 내 멤버 변수에 대한 정의문이다.
int S::a[10];
const int S::k = 3;

int main()
{
	S s;
	std::cout << s.m << std::endl;

	for (int i = 0; i < 10; ++i)
	{
		std::cout << s.a[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		std::cout << S::a[i] << " ";
	}
}
```

- 정적 멤버 변수의 초기화는 정의문을 통해 구현된다.
    - 정적 멤버 변수를 선언문에서 초기화한다면 에러 발생
- 상수와 상수표현식은 정적 멤버 변수여도 선언문에서 선언 즉시 초기화가 가능하다.

### 6 - 02 클래스와 구조체의 멤버

- 클래스와 구조체는 다음과 같은 멤버를 가질 수 있다.
    - 생성자 ( Constructor )
    - 연산자 오버로딩 ( Operator Overloading )
    - 소멸자 ( Destructors )
    - 내부 클래스 또는 내부 구조체
    - 함수 ( Function )
    - 데이터 타입
    - 변수와 상수 그리고 상수표현식

- 생성자
    - 클래스로부터 인스턴스를 생성하고 내부 멤버 변수를 초기화시키는 목적으로 사용한다.
    - 개발자가 클래스 내 생성자를 하나라도 만든다면, 컴파일러는 디폴트 생성자를 제공하지 않는다.
    - 인스턴스는 생성자의 본문이 실행되기 직전에 메모리의 영역을 잡아 생성된다.
    
    ```cpp
    지정자 클래스-이름(인수-리스트) noexcept [ : 초기화-리스트] { 본문 }
    ```
    
    - inline 지정자
    - explicit 지정자 : 명시적 생성자
    - noexcept 지정자 : 예외 발생 허용 X

- 초기화-리스트 ( Initializer Lists )
    - 생성자의 본문을 호출하기 전에 먼저 멤버들에 대해 초기화 작업을 수행
    - 상수 멤버도 명시 가능
    - 함수도 호출 가능
    - 프로그램 본문과 다르게 객체 생성과 함께 시스템(또는 운영체제) 내부에서 실행되기 때문에 작업 속도가 빠르다.

- 상수표현식 생성자
    - 상수표현식을 사용하면 더 빠름
    - 다음 조건하에서 상수표현식 생성자를 가질 수 있다.
        - 클래스가 상속받는 기본 클래스 내 가상 함수가 없을 때
        - 객체 생성 시 인수로 리터럴을 사용할 때
        - 클래스와 기본 클래스 내 존재하는 정적 변수를 제외한 모든 멤버 변수는 생성과 동시에 초기화될 때
        - 상수표현식 생성자 본문에 문장이 들어가면 에러 발생, 초기화 리스트에서 모두 초기화

```cpp
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

	// 1. 생성자의 인수로 리터럴을 사용하였으므로 사용이 가능하다.
	constexpr Complex Cx1(1.0, 0.9);

	// 2. constexpr 지정자로 선언한 인수는 상수가 되어야 한다. 따라서 생성자의 인수로
	//    변수를 사용한다면 x 변수의 값을 알 수 있다하더라도 에러가 발생한다.
	// constexpr Complex Cx1(x, 1);

	// 3. 다음 Cx2 변수는 constexpr 지정자로 선언된 상수가 아니기 때문에 허용된다.
	const Complex Cx2(x, 1); // Ok

	// 4. Comp 변수는 constexpr 지정자로 선언되어 있으므로 내부 변수 역시 모두
	//    상수이므로 다음과 같이 상수를 초기화하는 데 허용된다.
	constexpr double XX = Comp.GetReal(); // Ok
	constexpr double ImagVal = Comp.GetImag(); // Ok
	double xd = Comp.GetReal(); // Ok

	// 5. 상수표현식으로 선언된 생성자는 리터럴로 인식되므로 일반 변수를 생성하는 데
	//    사용하더라도 전혀 문제가 되지 않는다.
	Complex Cx3(2.0, 4.6);
	
	// int a;
	// Complex Cx4(a, 4.0); 에러!

	return 0;
}
```

- 연산자 오버로딩

```cpp
#include <iostream>

struct Simple
{
	// 객체를 생성하기 위해 메모리 공간을 확보하는 new 연산자 오버로딩이다.
	// new 연산자 오버로딩은 객체 생성 이전에 호출되는 연산자이므로 static 으로
	// 선언해주어야 한다.

	static void* operator new(std::size_t sz)
	{
		std::cout << "new called.\n";

		// 전역 네임스페이스 내 존재하는 new 연산자를 호출한다.
		return ::operator new(sz);
	}

	// 확보한 메모리 공간을 운영체제에 반환하는 delete 연산자 오버로딩이다.
	static void operator delete(void* ptr)
	{
		std::cout << "delete called.\n";

		::operator delete(ptr);
	}
};

int main()
{
	Simple* simple = new Simple;

	delete simple;
}

실행 결과
new called.
delete called.
```

- 소멸자
    - 객체 소멸 시 호출되는 함수
    - 객체가 메모리에서 내려갈 때 호출된다. ex) 지역 범위를 벗어난 경우, delete를 호출한 경우

- 내부 클래스
    - 내부 클래스는 클래스의 외부로부터 내부에서 사용하는 클래스를 감추기 위해 사용한다.

- this 포인터
    - 클래스 자기 자신을 가르키는 포인터

- 접근 지정자
    - public
    - protected
    - private

- 클래스와 구조체 멤버의 선언 순서 : 필수는 아니나 코딩 스타일 맞추면 편함
    - 접근 지정자 public, protected, private
    - using 지정자 typedef 지정자, 열거형 타입은 접근 지정자 바로 다음
    - 내부 클래스 또는 내부 구조체
    - 생성자
    - 소멸자
    - 멤버 함수나 정적 멤버 함수
    - 연산자 오버로딩
    - 일반 멤버 변수

### 6 - 03 객체의 초기화

객체의 초기화는 클래스 내 멤버 변수의 초기화를 의미한다. 그에 따라 객체를 초기화하는 방법으로 아래와 같은 예가 있을 수 있다.

```cpp
#include <iostream>

class SimpleClass
{
public:
	int Val;
};

int main()
{
	SimpleClass SC;
	SC.Val = 5;
	std::cout << SC.Val << std::endl;
	return 0;
}
```

- 정적 멤버 변수
    - 정적으로 선언된 변수와 상수는 클래스 외부에서 초기화해야 한다.
    - 정적으로 선언된 상수는 객체 생성 이전부터 이미 가지고 있는 데이터이기 때문에 생성자를 사용하여 정적 상수를 초기화시킬 수 없다.

```cpp
#include <iostream>

using std::cout;
using std::endl;

class Something
{
private:
	static int iValue;			// 정적 멤버 변수이다.
	static const int ciValue;   // 정적 멤버 상수이다.

public:
	// 정적 함수는 오로지 정적 멤버 변수나 정적 멤버 상수 그리고
	// 정적 함수만을 호출할 수 있다.
	// 정적 함수는 객체가 생성되지 않더라도 호출이 가능하므로 초기화 되어 있지 않은
	// 일반 멤버 변수나 함수를 사용할 수 없다.
	static int GetValue() { return iValue; }
	static const int GetConst() { return ciValue; }
};

int Something::iValue = 1; // 정적 멤버 변수를 초기화한다.
const int Something::ciValue = 10; // 정적 상수 멤버 변수를 초기화한다.

int main()
{
	cout << "Something::GetValue() = " << Something::GetValue() << endl;
	cout << "Something::GetConst() = " << Something::GetConst() << endl;
}
```

- 정적 멤버 변수 사용처
    - new 연산자
        - 클래스가 객체화되기 전에 요구하는 메모리 공간을 잡을 때 사용
    - 정적 멤버 변수는 클래스의 인스턴스가 서로 공유하는 변수를 만들 때 주로 사용한다.
    - 정적 연산자 오버로딩을 제외하고 일반 정적 멤버 함수는 선언과 사용에 있어 특정 클래스에 구속되지 않는다면, 다음과 같이 네임스페이스 내 전역 함수를 고려해볼 필요가 있다.

```cpp
클래스 내 정적 멤버 함수
namespace MyProject
{
	class A
	{
	public:
		static void Func();
	}
}

int main()
{
	MyProject::A::Func();
}
```

```cpp
네임스페이스 내 전역 함수
namespace MyProject
{
	namespace A
	{
		void Func();
	}
}

int main()
{
	MyProject::A::Func();
}
```

- 정적 함수(또는 변수)로 만들어 클래스에 묶을 필요가 없는 함수이라면 네임스페이스 내 전역 함수(또는 변수)를 선언하여 사용할 것을 권고한대용

### 6 - 04 클래스의 관계

- 연관 (association)
- 집합 (aggregation)
- 구성 (composition)
- 의존 (dependency)
- 상속 (inheritance)
- 구현 (realization)

### 6 - 05 클래스 상속

```cpp
#include <iostream>
#include <string>

struct Person
{
public:
	Person(std::string sName) : sName(sName) {}

	std::string& GetName() { return sName; }

private:
	std::string sName;
};

class Student : public Person
{
public:
	// 기본 클래스를 먼저 생성하고 자신의 멤버를 초기화시키는 것이 보기에 좋다.
	Student(std::string sName, std::string sId) : Person(sName), sId(sId) {}

	std::string& GetID() { return sId; }

private:
	std::string sId;
};

int main()
{
	Student S1("홍길동", "20056");

	std::cout << "이름 : " << S1.GetName() << ", 학번 : " << S1.GetID() << std::endl;

	return 0;
}
```

- C++ 상속 특징
    - 인터페이스 따로 제공 X
    - 구조체와 클래스 구분 없이 상속 가능
    - 다중 상속 가능
    - 최상위 클래스 X
    - 상속되지 않는 멤버
        - 생성자
        - 소멸자
        - 대입 연산자
        - 친구 관계로 지정된 함수 → 아마 friend 키워드 말하는듯

![image.png](https://prod-files-secure.s3.us-west-2.amazonaws.com/7ebf7000-f855-492a-973c-2e002d905ac7/65832b99-8928-4de2-a410-710f1ce9c2f7/image.png)

### 6 - 06 가상 함수

- 객체 지향 언어의 특성 중 하나 : 다형성
    - 객체 지향 언어의 다형성은 하나의 인터페이스를 통해 클래스가 가지고 있는 다양한 기능을 제공하는 것을 의미한다.
    - 다형성의 원칙은 클래스 내 멤버 함수를 호출할 때, 해당 클래스에서 정의한 함수가 아닌 상속으로 연결된 하위 클래스 내 정의한 함수가 호출되는 것을 의미한다.
- 가상 함수 (virtual function)
    - 가상함수는 다형성의 원칙을 충족시키기 위해 만들어진 함수이다.
    - 자신의 클래스를 상속받아 가상 함수를 구현한 하위 클래스 내 함수로 대처되어 호출된다.
    - virtual 지정자를 사용하면 클래스마다 vptr, vtable 생성

```cpp
#include <iostream>
#include <string>

using namespace std;

class Shape
{
public:
	Shape(string sName) : sName(sName) {}

	void Area() { cout << "도형 이름 : " << GetName() << ", 넓이 : " << GetArea(); }
	virtual double GetArea() { return 0; }

	const string& GetName() { return sName; }

private:
	string sName;
};

class Rectangle : public Shape
{
public:
	Rectangle(string sName, float fWidth = 0, float fHeight = 0) : Shape(sName), fWidth(fWidth), fHeight(fHeight) {}

	virtual double GetArea() override { return fWidth * fHeight; }

private:
	float fWidth;
	float fHeight;
};

class Triangle : public Rectangle
{
public:
	Triangle(float fWidth = 0, float fHeight = 0) : Rectangle("Triangle", fWidth, fHeight) {}

	virtual double GetArea() final override { return (Rectangle::GetArea()) / 2.f; }

};

const double PI = 3.141592;
class Circle : public Shape
{
public:
	Circle(double dRadius = 0) : Shape("Circle"), dRadius(dRadius) {}

	virtual double GetArea() override { return PI * dRadius * dRadius; }

private:
	double dRadius;
};

int main()
{
	Shape* Sp[] = {
		new Rectangle("직사각형", 10, 5),
		new Triangle(10, 5),
		new Circle(10)
	};

	for (Shape* S : Sp)
	{
		S->Area();
		std::cout << std::endl;
	}

	for (Shape* S : Sp)
	{
		delete S;
	}

	return 0;
}
```

- 추상 클래스와 추상 함수
    - 추상 함수 ( 순수 가상 함수 )
        - `virtual double GetArea() = 0;`
        - 추상 함수는 상속만을 목적으로 만들어진 함수
        - 추상 함수는 정적 함수가 될 수 없음, 반대도 마찬가지
    - 추상 클래스
        - 추상 함수가 하나라도 존재한다면, 해당 클래스는 추상 클래스가 됨
        - 객체 생성 불가능
        - 추상 클래스를 상속받으면 반드시 추상 함수 구현됨