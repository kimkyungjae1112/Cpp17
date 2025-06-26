# 타입 변환 연산자와 연산자 오버로딩 09

- 타입 변환 연산자
- 친구 지정
- 연산자 오버로딩
- 산술 연산자 오버로딩
- 기타 연산자 오버로딩
- 마무리

<br>

컴파일러는 연산 작업을 수행하기에 앞서 가장 먼저 변수의 데이터 타입을 통일시키는 작업을 수행한다. 프로그램 내 같은 문장이라 하더라도 컴파일러가 해석을 어떻게 하느냐에 따라 개발자가 원래 의도한 바와 다르게 진행될 수 있다.

- 암시적 변환
    - 컴파일러가 알아서 변환하는 방법
    - 개발자는 연산자와 피연산자 그리고 연산을 적용하는 데이터 타입간의 관계를 다른 무엇보다 잘 이해하고 있어야 한다.
- 명시적 변환
    - 개발자가 직접 변환하는 타입을 명시하는 방법

<br>

C언어 스타일의 명시적 변환은 타입 변환이 가능한 지 여부를 사전에 검사하지 않고 모든 판단을 개발자에게 맡긴다. 반면에 C++ 언어에서 변환 작업은 형식 변환이 아닌 하나의 연산 작업으로 인식하고 연산자를 사용해 변환을 진행한다. 따라서 사전에 변환이 가능한지 검사받을 수 있다.

- static_cast 연산자
- dynamic_cast 연산자
- const_cast 연산자
- reinterpret_cast 연산자
- 연산자 오버로딩
    - 친구 지정 : friend 지정자
    - 연산자 오버로딩 : 클래스의 연산 방법

<br>

### 9 - 01 타입 변환 연산자

- static_cast 연산자는 컴파일 시점에 타입 변환이 이루어진다.
- static_cast < 바꾸고자 하는 타입 > (expression)
- static_cast 연산자의 사용 방법
    - 일반 변환 : 일반 변환은 암시적 변환뿐만 아니라 명시적 변환 작업과 유사한 기능을 수행
    
    ```cpp
    #include <iostream>
    #include <vector>
    
    int main()
    {
    	int N = 100;
    	void* NV = &N; // 암시적 변환 작업을 수행
    
    	// long 타입의 포인터가 정수 타입의 변수를 가리키도록 만든다.
    	long* N01 = static_cast<long*>(NV);
    	int* N02 = static_cast<int*>(&N);
    
    	// 간접 참조를 사용하여 데이터를 출력시킨다.
    	std::cout << "N = " << N << ", *N01 = " << *N01 <<
    		" , *N02 = " << *N02 << '\\n';
    
    	std::vector<long> E = { 1,23,10 };
    	void* VoidP = &E; // void 타입의 포인터를 선언하고 컨테이너 객체의 주소를 넣음
    
    	// 컨테이너 객체가 관리하는 요소의 타입을 long 타입에서 int 타입으로 바꿈
    	std::vector<int>* Vec = static_cast<std::vector<int>*>(VoidP);
    
    	// 또 다른 컨테이너 객체에 데이터를 대입 복사
    	std::vector<int> Vr = *Vec;
    	for (int a : Vr)
    	{
    		std::cout << a << " ";
    	}
    	std::cout << std::endl;
    }
    
    ```
    
	<br>

    - 위의 코드같은 경우 윈도우 환경에선 long을 32비트로 인식하는 반면 리눅스 환경에선 long을 64비트로 인식한다.
    - 위와 같은 타입 변환은 본의 아니게 데이터 타입의 크기 변환으로 인식하기 때문에 문제가 발생할 수 있다.
- 열거형 타입으로부터 다른 열거형 타입으로 변환
    - 명시적 타입 변환을 그대로 아래와 같이 static_cast 연산자로 교체하여 사용하면 됨
    
    ```cpp
    #include <iostream>
    
    enum Days
    {
    	Sunday = 0, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
    };
    
    enum class Months : short
    {
    	Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
    };
    
    const char* Week[] = { "Sunday", "Monday", "Tuesday",
    						"Wednesday", "Thursday", "Friday", "Saturday" };
    
    // 열거형 타입의 요소로 제공되는 주의 이름을 문자열로 반환한다.
    const char* DayName(Days Day)
    {
    	if (Day < Sunday || Day > Saturday)
    		return "알 수 없는 날";
    	return Week[Day];
    }
    
    int main()
    {
    	Months ThisMonth = Months::Dec;
    
    	Days Today = static_cast<Days>(ThisMonth); // == Days Today = (Days) ThisMonth;
    	std::cout << DayName(Today) << "는 " << Today + 1 << "번째 요일이다." << std::endl;
    
    	Months NextMonth = (Months)((short)Months::Dec - 12 + 1);
    	Today = static_cast<Days>(NextMonth);
    	std::cout << DayName(Today) << "는 " << Today + 1 << "번째 요일이다." << std::endl;
    
    	// 열거형 타입의 요소로부터 int 또는 float 으로 변환은 다음과 같다.
    	float One = static_cast<float>(Today);
    	std::cout << DayName(Today) << "는 " << One + 1 << "번째 요일이다." << std::endl;
    
    	return 0;
    }
    
    ```
    
<br>

- 다운 캐스트 작업
    - Derived 클래스는 Base 클래스의 모든 것을 상속받았다면, 업캐스팅이 가능하다.
    
    ```cpp
    #include <iostream>
    using namespace std;
    
    class Base
    {
    public:
    	virtual void Dummy()
    	{
    		cout << "Base Dummy" << endl;
    	}
    };
    
    class Derived : public Base
    {
    public:
    	Derived(int i = 0) : Number(i) {}
    
    private:
    	int Number;
    };
    
    int main()
    {
    	Derived D;
    	Base& Br = D; // 참조를 사용하여 상위 Base 클래스의 객체로 변환한다.
    
    	// 하위 클래스의 객체로 변환할 때 다음과 같은 명시적 변환도 허용은 된다.
    	// Derived& Another_D = (Derived&) Br;
    	Derived& Another_D = static_cast<Derived&>(Br);
    	printf("D = %p, Br = %p, Another_D = %p\\n", &D, &Br, &Another_D);
    
    	Derived A[10];
    	Base* DP = static_cast<Base*>(A); // 업캐스팅
    
    	return 0;
    }
    
    ```
    
<br>

- 일반 변수를 rvalue 참조로 변환
    - rvalue 참조는 C언어에서 제공하지 않는 가상 변수 타입이다.
    
    ```cpp
    #include <iostream>
    
    int i = 0;
    
    // 1. lvalue 참조를 함수의 매개변수로 사용한다.
    void ParamCheck(int& s)
    {
    	std::cout << ++i << ", " << s << " 인수는 'int&' 타입이다.\\n";
    }
    
    // 2. lvalue 참조 상수를 함수의 매개변수로 사용한다.
    void ParamCheck(const int& s)
    {
    	std::cout << ++i << ", " << s << " 인수는 'const int&' 타입이다.\\n";
    }
    
    // 3. rvalue 참조 상수를 함수의 매개변수로 사용한다.
    void ParamCheck(int&& s)
    {
    	std::cout << ++i << ", " << s << " 인수는 'int&&' 타입이다.\\n";
    }
    
    int main()
    {
    	int s = 10;
    	ParamCheck(s); // 1번째 함수 호출
    
    	const int& cs = s;
    	ParamCheck(cs); // 2번째 함수 호출
    
    	// rvalue 참조로 변환한다.
    	ParamCheck(static_cast<int&&>(s)); // 3번째 함수 호출
    
    	return 0;
    }
    
    ```
    
	<br>

    - rvalue 참조로 타입 변환은 std::move() 함수나 std::forward() 함수를 사용하는 것이 좋음
- const_cast 연산자
    - const 상수를 일반 변수로 변환하여 데이터의 수정이 가능하게 만들어 주는 기능 제공
    
    ```cpp
    const int i = 3;
    const_cast<int&>(i) = 4; // 상수를 참조로 변환
    
    const int j = 3;
    int* pj = const_cast<int*>(&j); // cosnt를 제거하고 포인터로 만듬
    *pj = 8;
    
    실행 결과
    i = 3
    *pj = 8, j = 3
    //값이 다름!
    
    ```
    
    - 컴파일러가 프로그램을 최적화시켜 상수를 메모리 저장소가 아닌 CPU 캐시에 보관하고 사용하기 때문에 발생하는 현상
    - const_cast() 연산자는 CPU 캐시 내 저장된 데이터를 가리키는 상수를 변수로 만드는 것이 아니라 메모리에 위치한 저장소를 상수에서 변수로 바꾸어 인식하는 기능을 제공
    - volatile 지정자를 넣어 해당 상황을 해결 가능
    
    ```cpp
    const volatile int i = 3; //cv 타입 한정자 (const volatile type qualifier)
    // volatile 은 캐시에 저장되는 것을 막는 지정자
    
    ```
    
    - const_cast 연산자는 포인터와 참조에 대해서만 적용이 가능
- dynamic_cast 연산자
    - 클래스와 구조체의 상속 구조를 이용하여 상위 클래스의 객체로 업-캐스트 하거나 또는 하위 클래스의 객체로 다운-캐스트하는 기능을 제공한다.
    - 만약 포인터를 사용하여 정상적으로 변환이 이루어지지 않는다면, nullptr 를 반환한다.
    - 만약 참조를 사용한다면 NULL 값을 반환할 수 없기 때문에 예외를 발생시킨다.
    
    ```cpp
    #include <iostream>
    using namespace std;
    
    class Base
    {
    public:
    	Base() : State(0) {}
    	Base(int i) : State(i) {}
    
    	virtual int Dummy()
    	{
    		cout << "Base Dummy" << endl;
    		return State;
    	}
    private:
    	int State;
    };
    
    class Derived : public Base
    {
    public:
    	Derived(int i = 0) : Base(i) {}
    	void SetNumber(int i) { Number = i; }
    
    	int Number;
    };
    
    int main()
    {
    	Derived* PD;
    	Base* PBA = new Derived(23);
    
    	// Base 타입의 객체를 Derived 객체로 변환
    	// 업캐스팅 된것을 다시 되돌려놓는 것
    	PD = dynamic_cast<Derived*>(PBA);
    	if (PD == nullptr) std::cout << "첫 번째 PBA 객체의 변환이 실패함" << std::endl;
    
    	PD->SetNumber(10);
    	std::cout << PD->Number << std::endl;
    	std::cout << PD->Dummy() << std::endl;
    	delete PBA;
    
    	Base* PBB = new Base(568);
    	PD = dynamic_cast<Derived*>(PBB);
    	if (PD == nullptr) std::cout << "두 번째 PBB 객체의 변환이 실패함" << std::endl;
    
    	// static_cast를 통해 정상 작동하는 것처럼 보이나 실제 다른 영역을 침범하여 작업이 이루어진다.
    	PD = static_cast<Derived*>(PBB);
    	PD->SetNumber(110);
    	std::cout << PD->Number << std::endl;
    	std::cout << PD->Dummy() << std::endl;
    	delete PBB;
    
    	return 0;
    }
    
    ```
    
- reinterpret_cast 연산자
    - 프로그램이 실행되는 시점에 변환이 이루어진다. → 위험성 높음

<br>

### 9 - 02 친구 지정

- 클래스 내부에서 friend 지정자를 사용하여 다른 함수나 다른 클래스를 친구로 선언한다면, 상속관계가 없는 친구 클래스나 함수라 하더라도 마치 클래스의 멤버인 것처럼 클래스 내부 모든 멤버의 접근이 허용된다.

```cpp
#include <iostream>

class Ours;

class Friend
{
public:
	int Func1(Ours& b);

private:
	int Func2(Ours& b) {}
};

class Ours
{
public:
	Ours(int i) : _b(i) {}

private:
	int _b;

	friend int Friend::Func1(Ours&);
};

int Friend::Func1(Ours& b) { return b._b; }

// friend가 아니라면 private 에 접근 불가능
// int Friend::Func2(Ours& b) { return b._b; }

int main()
{
	Ours Our(1);

	Friend friend1;
	std::cout << friend1.Func1(Our) << std::endl;
}

```

```cpp
#include <iostream>

class Ours;

class Friend
{
public:
	int Func1(Ours& b);

private:
	int Func2(Ours& b) {}
};

class Ours
{
public:
	Ours(int i) : _b(i) {}

private:
	int _b;

	friend class Friend;
};

int Friend::Func1(Ours& b) { return b._b; }

// friend가 아니라면 private 에 접근 불가능
// class로 지정하면 접근 가는ㅇ
int Friend::Func2(Ours& b) { return b._b; }

int main()
{
	Ours Our(1);

	Friend friend1;
	std::cout << friend1.Func1(Our) << std::endl;
}

```

- 함수 또는 연산자 검색
    - 함수가 범위 확인 연산자와 함께 다음과 같이 정규화되어 있다면, 우선적으로 해당 네임스페이스를 가지고 있는 라이브러리에서 malloc() 함수를 찾는다.
    
    ```cpp
    this->name = (char*)std::malloc(strlen(name) + 1);
    
    ```
    
    - 상속 관계에 있는 모든 클래스로부터 멤버 함수 오버로딩을 찾는다.
    - 함수가 특정 네임스페이스 내 함수나 클래스의 멤버 함수가 아니라면, 컴파일러는 해당 프로그램내에서 전역 함수나 지역 함수를 찾는다.
    - 위의 조건 내 함수가 존재하지 않는다면, 인수 의존 검색을 수행한다.
        - 인수 의존 검색은 코에니크 검색이라 하여 함수 내 인수의 데이터 타입을 통해 해당 함수를 찾는 기법을 말한다.
    - 개별 클래스에서 서로의 타입으로 변환시키는 타입 변환 연산자 오버로딩을 먼저 찾게 된다.
    - 만약 찾을 수 없다면, 컴파일러는 다음 작업으로 << 연산자 내 인수의 데이터 타입으로부터 << 연산자 오버로딩을 찾게 된다.
- 내가 만든 클래스 cout 으로 출력하기

```cpp
friend std::ostream& operator<<(std::ostream& os, const KlassName& k);

```

- 위의 함수는 전역 함수로 인식된다.

```cpp
friend std::ostream& operator<<(std::ostream& os, const KlassName& k)
{
	os << "연산자" << "오버로딩";
	return os;
}

```

```cpp
std::cout << "첫번째" << "두번째";

```

- 위의 코드는 (std::cout << “첫번째) << “두번째
    - 괄호 안의 코드가 먼저 수행되고 그 다음 std::cout << “두번째” 작업을 수행한다.
    - 함수 체이닝
- C++ 언어는 설계 관점에서 접근 제한이 클래스 중심으로 되어 있어 같은 클래스로부터 생성된 객체는 private으로 선언되어 있다 하더라도 선언과 무관하게 접근이 허용된다.

```cpp
class Person
{
public:
	Person(std::string N, int A) : Name(N), Age(A) {}

	bool Compare(const Person& P)
	{
		// Name과 Age는 private으로 선언되어 있다하더라도 같은 클래스이므로
		// 아래와 같이 자신과 인수 모두 사용이 가능하다.
		return (this->Age < P.Age) ? false : true;
	}

private:
	std::string Name;
	int Age;

```

- 친구 관계와 클래스 상속
    - 클래스간의 상속이 이루어진다 하더라도 친구 사이의 관계까지 상속이 이루어지지 않는다.

<br>

### 9 - 03 연산자 오버로딩

- 포맷
    - 연산자 오버로딩은 다음과 같이 operator 키워드와 함께 연산자를 사용하여 정의한다.
        
        반환되는 데이터 타입 operator연산자(매개변수) { 본문 }
        
- 멤버 연산자 오버로딩
    - 자기 자신 객체를 기준으로 같은 클래스 타입 또는 다른 데이터 타입의 인수와의 연산 작업을 수행하는 함수
    - 반환하는 데이터 타입이 인수의 데이터 타입과 동일한 특성
- 전역 연산자 오버로딩
    - 다른 타입의 데이터를 반환하는 연산
- 오버로딩 가능한 연산자
    - 42개 있음
    - 대입 연산자( ‘=’ ), 함수 호출 연산자,( ‘()’ ), 배열 인덱스 연산자( ‘[]’ ), 포인터 멤버 선택 연산자(’→’)는 오로지 클래스의 멤버 연산자 오버로딩으로만 정의가 가능하다.
    - 다음은 권고 사항
        - 단항 연산자는 클래스 멤버 연산자 오버로딩으로 구현한다.
        - 이항 연산자 가운데 연산 결과가 객체에 반영되지 않는다면, 멤버 연산자 오버로딩으로도 가능하지만 되도록 전역 연산자 오버로딩으로 구현하는 것이 좋다.
        - 기본 연산자에 대한 오버로딩은 사용하지 않는 것이 좋다.
        - 논리 연산자는 ‘짧은 회로 평가’ 방식으로 참, 거짓을 선별하기에 가급적 오버로딩 하지 않는 것이 좋다.
    - 3가지 기본 법칙
        - 논쟁의 소지가 있다면, 해당 연산자는 오버로딩 하지 않는다.
        - 연산자 오버로딩은 보편적인 상식을 기준으로 한다.
        - 연관된 연산자 모두를 오버로딩해야 한다.

<br>

### 9 - 04 산술 연산자 오버로딩

복소수 구조체로 연산자 오버로딩 연습을 해보자.

```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <cmath>

struct Complex
{
public:
	constexpr Complex(double dReal);
	constexpr Complex(double dReal, double dImaginary);

	// 1. 단항 연산자 오버로딩
	Complex& operator+();
	Complex operator-();

	// 전위 연산자 오버로딩이 반환하는 객체는 *this에 대한 참조이다. 반면에 후위 단항 연산자는 함수
	// 내부에서 임시 객체를 생성하여 반환한다. 임시 객체는 '복사 이동 생략의 원칙'에 따라
	// 일반 객체로 변형된다.
	Complex& operator++();		// ++ 전위 연산자 오버로딩
	Complex operator++(int);	// ++ 후위 연산자 오버로딩
	Complex& operator--();		// -- 전위 연산자 오버로딩
	Complex operator--(int);	// -- 후위 연산자 오버로딩

	// 2. 이항 산술 연산자 오버로딩
	// 아래 이항 산술 연산자의 작업 결과는 rvalue 이다. 따라서 연산 작업 결과는 임시 객체를 만들어
	// 반환한다. 또한 이항 연산자 오버로딩은 아래와 같이 inline(또는 상수 표현식)으로 선언이
	// 가능하며, 또한 전역 연산자 오버로딩으로 만들어도 좋다.
	// inline constexpr Complex operator+(const Complex& lhs) const;
	Complex operator+(const Complex& c) const;
	Complex operator-(const Complex& c) const;
	Complex operator*(const Complex& c) const;
	Complex operator/(const Complex& c) const;

	// 대입 연산자 작업 결과는 자체 객체의 변화를 발생시키므로 다음과 같이 참조를 사용한다.
	// 여기서는 복사 대입 연산자만 선언하였다.
	Complex& operator=(const Complex& c);
	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);

	// 이항 비교 연산자 오버로딩(필요하다면 전역 연산자 오버로딩으로 만들어도 좋다)
	bool operator==(const Complex& c);
	bool operator!=(const Complex& c);

	// 3. 타입 변환 연산자 오버로딩 (Complex -> double 또는 Complex -> char)
	//    자기 자신의 객체를 정수 또는 실수로 만들어 준다.
	operator double();

	// 'std<<cout << Complex(x, y)' 처럼 복소수를 출력하기 위해 오버로딩을 해주어야 한다.
	friend std::ostream& operator<<(std::ostream& os, const Complex& c);

	// 변수의 데이터를 반환한다.
	inline double GetReal() const { return dReal; }
	inline double GetImaginary() const { return dImaginary; }

private:
	double dReal;
	double dImaginary;
};

constexpr Complex::Complex(double dReal) : dReal(dReal), dImaginary(0.0)
{

}

constexpr Complex::Complex(double dReal, double dImaginary) : dReal(dReal), dImaginary(dImaginary)
{

}

Complex& Complex::operator+()
{
	return *this;
}

// - 단항 연산자의 작업 결과는 rvalue(임시 객체)를 만들어 반환한다.
// 그리고 RVO 복사/이동 생략의 원칙에 따라 객체가 된다.
Complex Complex::operator-()
{
	Complex complex(-this->dReal, -this->dImaginary);
	return complex;
}

Complex& Complex::operator++()
{
	++this->dReal;
	++this->dImaginary;
	return *this;
}
Complex Complex::operator++(int)
{
	Complex complex(this->dReal, this->dImaginary);
	++this->dReal;
	++this->dImaginary;
	return complex;
}
Complex& Complex::operator--()
{
	--this->dReal;
	--this->dImaginary;
	return *this;
}
Complex Complex::operator--(int)
{
	Complex complex(this->dReal, this->dImaginary);
	--this->dReal;
	--this->dImaginary;
	return complex;
}

Complex Complex::operator+(const Complex& c) const
{
	return Complex(this->dReal + c.dReal, this->dImaginary + c.dImaginary);
}
Complex Complex::operator-(const Complex& c) const
{
	return Complex(this->dReal - c.dReal, this->dImaginary - c.dImaginary);
}
Complex Complex::operator*(const Complex& c) const
{
	return Complex(
		(this->dReal * c.dReal - this->dImaginary * c.dImaginary),
		(this->dReal * c.dImaginary + this->dImaginary * c.dReal));
}
Complex Complex::operator/(const Complex& c) const
{
	double r = (this->dReal * c.dReal + this->dImaginary * c.dImaginary) /
		((c.dReal * c.dReal) + (c.dImaginary * c.dImaginary));

	double i = (this->dReal * c.dImaginary - this->dImaginary * c.dReal) /
		((c.dReal * c.dReal) + (c.dImaginary * c.dImaginary));

	return Complex(r, i);
}

Complex& Complex::operator=(const Complex& c)
{
	this->dReal = c.dReal;
	this->dImaginary = c.dImaginary;
	return *this;
}
Complex& Complex::operator+=(const Complex& c)
{
	this->dReal += c.dReal;
	this->dImaginary += c.dImaginary;
	return *this;
}
Complex& Complex::operator-=(const Complex& c)
{
	this->dReal -= c.dReal;
	this->dImaginary -= c.dImaginary;
	return *this;
}

bool Complex::operator==(const Complex& c)
{
	return this->dReal == c.dReal && this->dImaginary == c.dImaginary;
}
bool Complex::operator!=(const Complex& c)
{
	return !operator==(c);
}

Complex::operator double()
{
	return this->dReal;
}

std::ostream& operator<<(std::ostream& os, const Complex& c)
{
	os << "( " << c.dReal << " + " << c.dImaginary << "i" << " )";
	return os;
}

int main()
{
	Complex c1(10, 20);
	Complex c2(30, 40);
	std::cout << c1 << c2 << std::endl;
	return 0;
}

```

<br>

### 9 - 05 기타 연산자 오버로딩

- ‘( )’ 함수 호출 연산자 오버로딩
    - 클래스 내 ‘( )’ 함수 호출 연산자 오버로딩을 호출하여 변수를 함수처럼 사용할 수 있다.
    - function 객체와 bind() 함수를 사용하여 다른 함수를 대입하여 호출할 수 있다.
    - 람다를 사용한다.
    
    ```cpp
    #include <iostream>
    #include <string>
    
    class Box
    {
    public:
    	Box(int Width = 0, int Length = 0, int Height = 0) :
    		Width(Width), Length(Length), Height(Height)
    	{
    		std::cout << "Box( ," << Width << ", " << Length << ", " << Height <<
    			" ) 생성자가 호출 되었습니다." << std::endl;
    	}
    	~Box()
    	{
    		std::cout << "Box 소멸자가 호출되었습니다." << std::endl;
    	}
    
    	// 아래 함수 호출 연산자 오버로딩은 인수가 void 타입일 때 사용하는 함수이다.
    	// 예는 박스의 부피를 계산하여 반환한다.
    	int operator()()
    	{
    		return Width * Length * Height;
    	}
    
    	// 아래 함수 호출 연산자 오버로딩은 높이를 수정할 수 있는 인수를 제공한다.
    	int operator()(int h)
    	{
    		return Width * Length * h;
    	}
    
    private:
    	int Width;
    	int Length;
    	int Height;
    
    };
    
    int main()
    {
    	Box sb(10, 20, 30);
    
    	std::cout << sb() << std::endl;
    	std::cout << sb(2) << std::endl;
    }
    
    ```
    
- 배열 인덱스 연산자 오버로딩
    - 배열 인덱스 연산자 오버로딩은 배열이나 컨테이너 클래스를 만들 때 사용한다.
    
    ```cpp
    #include <iostream>
    #include <cassert>
    
    template<typename Type>
    class Array
    {
    public:
    	typedef std::size_t SizeType;
    
    	// 생성자는 제공된 인수를 사용하여 아래와 같이 배열을 만드는 작업을 수행한다.
    	Array(SizeType Size) : Size(Size)
    	{
    		Data = new Type[this->Size];
    	}
    
    	// 소멸자를 사용하여 생성자에서 생성한 배열을 만드는 작업을 수행한다.
    	~Array()
    	{
    		if (Data)
    		{
    			delete[] Data;
    			Size = 0;
    		}
    	}
    
    	// 배열의 크기를 반환한다.
    	inline SizeType GetSize() const { return Size; }
    
    	// 아래 배열 인덱스 연산자 오버로딩은 배열의 요소를 수정할 때 사용한다.
    	Type& operator[](SizeType Index)
    	{
    		assert(Index >= 0 && Index < Size);
    		return Data[Index];
    	}
    
    	// 아래 배열 인덱스 연산자는 배열의 요소를 출력할 때 사용한다.
    	const Type& operator[](SizeType Index) const
    	{
    		assert(Index >= 0 && Index < Size);
    		return Data[Index];
    	}
    
    private:
    	Type* Data;
    	SizeType Size;
    };
    
    int main()
    {
    	Array<double> array(4); // 배열의 크기를 4로 잡는다.
    	// 배열 인덱스 오버로딩을 통해 다음과 같이 값을 입력시킬 수 있다.
    	// 아래 인덱스는 'Type& operator[](SizeType Index)' 연산자 오버로딩을 호출한다.
    	array[0] = 2.3;
    	array[1] = 3.3;
    	array[2] = 4.3;
    	array[3] = 12.3;
    
    	for (size_t i = 0; i < array.GetSize(); ++i)
    	{
    		std::cout << array[i] << " ";
    	}
    	return 0;
    }
    
    ```
    
    - Array 클래스 내 Data 변수는 접근 지정자가 private 이지만 함수에서 참조로 반환 시 데이터의 수정이 가능
    - 접근 제어는 어디까지나 변수나 함수에 대한 직접적인 접근의 기능 여부를 확인하는 특징을 제공
    - public 접근 지정자를 통해 반환받은 멤버 변수의 참조는 언제라도 수정 가능
    - 배열 인덱스 연산자를 오버로딩 할 때 const로 선언된 연산자와 그렇지 않은 연산자 두 개를 만들어야 함 → 하나는 데이터 수정, 하나는 데이터 조회
- new 연산자와 delete 연산자 오버로딩

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>

// 매개변수의 데이터 타입은 'stddef.h' 내 정의된 size_t 타입을 사용한다.
// 인수로 제공된 sz는 컴파일러가 알아서 객체의 크기를 계산하여 제공된다.
void* operator new(size_t sz)
{
	std::cout << "new called 크기 : " << sz << std::endl;
	return std::malloc(sz);
}

// new 연산자를 오버로딩하였다면, delete 연산자 역시 오버로딩해 주어야 한다.
// c++11 때부터 noexcept라는 키워드를 사용해야한다.
void operator delete(void* ptr) noexcept
{
	std::cout << "delete called\\n";
	std::free(ptr);
}

class MyString
{
	char* mData;
	size_t mDataLength;
};

int main()
{
	// new 연산자를 호출하면 우선적으로 전역 new 연산자 오버로딩을 호출한다.
	int* p1 = new int;
	delete p1;

	int* p2 = new int[10];
	delete[] p2;

	MyString* p3 = new MyString();
	delete p3;
}

```

- 만약 특정 클래스로 new 연산자와 delete 연산자를 한정시키려면, 다음과 같이 클래스 내부로 넣어주면 된다.

```cpp
#include <iostream>
#include <new>

class MyString
{
public:
	static void* operator new(size_t sz)
	{
		std::cout << "new called 크기 : " << sz << std::endl;
		return std::malloc(sz);
	}

	static void operator delete(void* ptr)
	{
		std::cout << "delete called\\n";
		std::free(ptr);
	}

private:
	char* mData;
	size_t mDataLength;
};

```

<br>

### 9 - 06 마무리

- 캐스팅 연산자
    - static_cast 연산자는 컴파일 시점에 적용된다.
    - dynamic_cast 연산자는 객체에 대한 변환을 위해 사용한다. 만약 포인터를 사용하여 정상적으로 변환이 이루어지지 않는다면 nullptr를 반환한다. 그러나 만약 참조를 사용한다면, nullptr 값을 반환할 수 없기 때문에 std::bad_cast라고 하는 예외를 발생시킨다.
    - dynamic_cast 연산자는 반드시 포인터나 참조에 대해서만 적용이 가능하다.
    - reinterpret_cast 연산자는 const_cast 연산자가 제공하는 변환을 제외하고 다른 모든 변환 연산자의 기능을 지원한다.
    - const_cast 연산자는 상수를 일반 변수로 변환시키는 기능을 제공하지만, 자칫 문제를 일으킬 수 있으므로 주의해야 할 연산자이다.
    - const_cast 연산자나 dynamic_cast 연산자는 일반 변수에 적용 시 에러가 발생한다.
- 연산자 오버로딩

![image.png](https://prod-files-secure.s3.us-west-2.amazonaws.com/7ebf7000-f855-492a-973c-2e002d905ac7/b3a8b0a5-a961-436f-a891-bcb5394fd543/image.png)