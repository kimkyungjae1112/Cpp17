# 클래스 생성자와 소멸자 07

- 생성자
- 소멸자
- 복사 생성자
- 얕은 복사와 깊은 복사
- 이동 생성자와 이동 대입 연산자
- 복사/이동 생략의 원칙
- 마무리

객체는 생성하는 과정을 통해 객체의 특성이 결정된다.

- 복사 생성자
- 소멸자
- 복사 대입 연산자
- 이동 생성자
- 이동 대입 연산자

### 7 - 01 생성자

주의사항

1. 생성자 본문에서 가상함수 호출 X
2. 생성자 내부에서는 가급적 예외를 발생시키지 말자 noexcept 지정자 사용
3. 기존 객체를 복사하여 생성자의 새로운 인수를 만드는 작업은 반드시 생성자의 인수 리스트에서 수행하는 것이 좋다.
4. 생성자는 일반 함수와 달리 메모리 주소를 알 수 없다.

```cpp
#include <iostream>
#include <cstdio>

class Complex
{
public:
	Complex(int x) : real(x), imaginary(0.0)
	{
		std::cout << "Complex(int x) 호출" << std::endl;
	}

	Complex(double x, double y) : real(x), imaginary(y)
	{
		std::cout << "Complex(double x, double y) 호출" << std::endl;
	}

private:
	double real;
	double imaginary;
};

int main()
{
	// 1. Ok : 숫자를 인수르 인식하여 Complex::Complex(int) 생성자를 호출한다.
	Complex a1 = 1;

	// 2. Ok : 직접 Complex::Complex(int) 생성자를 호출한다.
	Complex a2(2);

	// 3. Ok : 직접 Complex::Complex(double, double) 생성자를 호출한다.
	Complex a3{ 4,5 };

	// 4. Ok : 숫자를 인수로 만들어 Complex::Complex(double, double) 생성자를 호출한다.
	Complex a4 = { 4,5 };

	// 5. Ok : 아래 변환 작업은 Complex::Complex(int) 생성자를 호출한다.
	Complex a5 = (Complex)1;
	
	Complex* a6 = new Complex(4, 5);
	delete a6;
}
```

- 암시적 변환 생성자
    - 컴파일러는 자의적 해석에 따라 객체 생성 시 하나의 생성자를 선택하게 된다.
    - ‘=’ 대입연산자는 왼쪽 변수의 데이터 타입에 맞추어 변환하는 작업을 수행한다.

- 컴파일러는 다음과 같은 방식 가운데 하나를 선택하여 a1 객체를 생성하게 된다.
    - 첫 번째 방식 : 복사 생성자를 사용한다.
        - 1을 인수로 Complex(int x) 생성자를 호출하여 임시 Complex 객체를 만든다.
        - 임시 Complex 객체를 인수로 복사 생성자를 사용하여 a1 객체를 생성한다.
        - 임시 Complex 객체를 삭제한다.
    - 두 번째 방식 : 일반 생성자를 사용한다.
        - 1을 인수로 다음과 같이 Complex 생성자를 호출하여 a1 이란 Complex 객체를 생성한다.
        - `Complex a1(1)`

- 복사 생략
    - 컴파일러는 복사 생성자의 호출을 줄이는 방식으로 작업을 선택한다.
    - 거의 두 번째 방식으로 객체 생성

- explicit 지정자
    - 컴파일러가 자의적인 해석을 금지하고 자신이 설정된 방식으로만 객체를 생성하도록 기능 제공
    - 명시적 생성자

- 생성자 상속
    
    ```cpp
    #include <iostream>
    
    class Box
    {
    public:
    	Box(int width = 0, int length = 0, int height = 0) : 
    		width(width), length(length), height(height) {}
    
    	inline int GetVolume() { return width * length * height; }
    
    private:
    	int width;
    	int length;
    	int height;
    };
    
    class WoodBox : public Box
    {
    public:
    	// "uinsg Box::Box;" 선언문은 아래 라인과 동일한 기능을 수행
    	// WoodBox(int w, int l, int h) : Box(w, l, h) {}
    	using Box::Box;
    };
    
    int main()
    {
    	WoodBox* WB = new WoodBox(5, 10, 3);
    	WB->GetVolume();
    	delete WB;
    }
    ```
    

### 7 - 02 소멸자

- 소멸자는 클래스의 인스턴스가 삭제되기 전에 수행되는 특수 목적의 함수를 말한다.
- 다음과 같은 경우에 호출된다.
    - 프로그램이 종료되어 객체를 삭제시킬 때
    - 함수 내 지역 변수처럼 특정 지역 내 선언된 변수가 식별자 적용 범위를 벗어나 더 이상 사용할 수 없을 때
    - new 연산자를 사용하여 생성된 클래스의 인스턴스를 삭제시키기 위해 delete 연산자를 호출할 때

- 소멸자 특징
    - 소멸자는 인수를 갖지 않는다.
    - 소멸자는 클래스에서 하나만이 존재할 수 있다.
    - 상속이 이루어지지 않는다.
    - 하위 클래스의 소멸자가 호출되면 상위 클래스 소멸자 자동 호출 → 예외 있음
    - 인위적인 호출 가능 하지만 인위적으로 호출 시 문제 발생 가능
    - 의미없이 비어있는 소멸자를 만들지 않는 것이 좋다. 운영체제는 객체를 삭제하기 전에 소멸자를 작업 큐에 넣고 하나씩 수행한다.

- 가상 소멸자
    - 업캐스팅하여 객체 사용시 상위 클래스의 소멸자만이 불림
    - virtual 키워드를 붙여 소멸자를 만들자.

### 7 - 03 복사 생성자

- 복사 생성자는 기존 객체를 복사하여 새로운 객체를 생성하는 생성자이다.
- 함수 호출과 데이터 반환 시 다른 객체 지향 언어에 비해 객체의 복사가 빈번히 발생하게 된다.
- 깊은 복사 문제와 같이 해결해야 할 문제가 있는 것이 아니라면 복사 생성자를 만들지 않는 것이 좋다.

### 7 - 04 얕은 복사와 깊은 복사

- 얕은 복사
    - 포인터가 가르키고 있던 주소만 복사
- 깊은 복사
    - 새롭게 메모리를 할당하고 문자열이나 객체를 복사

### 7 - 05 이동 생성자와 이동 대입 연산자

- rvalue 참조를 사용하는 생성자
    - rvalue 참조
        - 상수(prvalue)나 임의 저장소(xvalue)를 참조하는 개념으로 rvalue 참조 선언 시 데이터 타입에 더블 엠퍼센트(’&&’)를 붙여 표기한다.
        - `<Type>&& Name`
        - 프로그램의 성능 향상과 프로그램의 개발 생산성에 초점이 맞추어져 만들어진 개념

일반변수

```cpp
void Func()
{
	int value = 10;
}

작업 내용
1. value 변수를 생성하고 10을 입력한다.
2. 함수 반환 시 변수를 소멸시킨다.
```

rvalue 참조

```cpp
void Func()
{
	int&& value = 10;
}

작업 내용
1. 저장소를 만들어 10을 입력한다.
2. 저장소에 대해 rvalue 참조를 만든다.
3. 함수 반환 시 임시 저장소와 함께
rvalue 참조를 소멸시킨다.
```

- rvalue 참조는 일반 변수를 초기화할 용도로 만들어진 것은 아님
    - 객체를 생성할 때 사용하는 이동 생성자와 이동 대입 연산자의 인수로 사용함
    - 완벽한 포워딩(Perfect Forwarding) 이라 하여 함수 오버로딩의 개수를 줄이는데 사용한다.

- 이동 생성자와 이동 대입 연산자
    - rvalue 참조를 사용하여 객체를 초기화 시키는 목적
    - 인수로 사용한 객체와 새롭게 생성한 객체의 멤버간의 데이터 교환이 아래와 같이 이루어진다.
    
    ```cpp
    //Other 객체는 작업이 완료된 이후에 소멸된다.
    MyString::MyString(MyString&& Other) noexcept : data(nullptr), length(0)
    {
    	std::swap(this->data, Other.data);
    	std::swap(this->length, Other.length);
    }
    ```
    
    - 따라서 객체간의 데이터가 복사가 아닌 교환을 통해 이루어지므로 옅은 복사라 하더라도 전혀 문제가 발생하지 않는다.
    - 개발자가 이동 생성자, 이동 대입 연산자를 제공하지 않는다면, 컴파일러는 복사 생성자와 복사 대입 연산자를 사용하여 작업을 수행한다.
    - 디폴트 이동 생성자, 이동 대입 연산자를 제공하지 않음

```cpp
class MyString
{
	MyString(const char* N = nullptr);
	MyString(const MyString& Other);
	MyString(MyString&& Other) noexcept; // 이동 생성자 선언
	~MyString();

	MyString& operator=(const MyString& Other);
	MyString& operator=(MyString&& Other) noexcept;

	void SetString(const char* N);
	const char* GetString() const;
	int GetLength() const;

private:
	char* cData;
	int iLength;
};

```

- 이동 생성자는 상호 멤버들간의 이동을 통해 리소스를 가리키는 포인터를 단일 포인터로 유지시킨다.
- 복사와 교환
    - swap() 함수를 사용하여 멤버 변수의 데이터를 서로 교체하면 편함

### 7 - 06 복사/이동 생략의 원칙

- 최적화 명목으로 복사 생성자와 이동 생성자의 호출을 생략할 수 있다.
    - 암시적 변환 생성자 → Complex x(1) 문장과 동일한 문장으로 취급
        - Complex x = 1 or Complex x = Complex(Complex(1));
    - 함수 내 지역 변수를 생성하여 반환하는 경우 (NRVO : Named Return Value Optimization)
        
        ```cpp
        // 반환 타입은 참조가 아닌 일반 타입이어야 한다.
        MyString Create(const char* ptr = nullptr)
        {
        	MyString obj(ptr); // 지역 변수 생성
        	return obj;        // 복사 생성자를 호출하지 않는다.
        }
        
        MyString x = Create("HelloWorld"); // 일반 생성자 하나만 호출한다.
        MyString* P = new MyString(Create("Hello World")); // 일반 생성자 하나만 호출한다.
        ```
        
        - 지역 변수는 const 지정자와 volatile 지정자가 없는 순수한 변수이어야 한다.
    - 함수가 다음과 같이 객체를 생성하여 반환하는 경우에 이동 생성자의 호출이 생략된다. (RVO : Return Value Optimization)
        
        ```cpp
        // 함수의 반환되는 데이터 타입은 참조가 아닌 일반 타입이어야 한다.
        MyString Create(const char* ptr = nullptr)
        {
        	return MyString{ptr}; // 무명 변수를 생성한다.
        }
        
        MyString x = Create();
        ```
        
    - 함수 내부에서 객체를 생성하여 throw를 사용하여 예외를 던졌을 때, 복사 생성자의 호출이 생략된다.
        
        ```cpp
        void Foo(const char* ptr = nullptr)
        {
        	throw MyString(ptr);
        }
        
        int main()
        {
        	try
        	{
        		foo("throw MyString");
        	}
        	catch(MyString& c)
        	{
        	
        	}
        }
        ```
        

```cpp
#include <iostream>
#include <string>
#include <algorithm>

int Count = 0;

class MyString
{
public:
	MyString(const char* ptr = nullptr) : sData(ptr)
	{
		std::cout << "Constructor : " << ptr << std::endl;
	}
	MyString(const MyString& Other) : sData(Other.sData)
	{
		std::cout << "Copy Constructor : " << sData.c_str() << std::endl;
		++Count;
	}
	MyString(MyString&& Other) noexcept
	{
		std::swap(this->sData, Other.sData);
		std::cout << "Move Constructor : " << sData.c_str() << std::endl;
		++Count;
	}
	~MyString()
	{
		std::cout << "Destructor : " << sData.c_str() << std::endl;
	}

	MyString& operator=(const MyString& Other)
	{
		if (this != &Other)
		{
			sData = Other.sData;
		}
		printf("MyString& MyString::operator = (MyString& %s\n ", this->sData);
		++Count;
		return *this;
	}
	MyString& operator=(MyString&& Other) noexcept
	{
		if (this != &Other)
		{
			std::swap(sData, Other.sData);
		}
		printf("MyString& MyString::operator = (MyString&& %s\n ", this->sData);
		++Count;
		return *this;
	}

private:
	std::string sData;
};

MyString Fun123(const char* ptr = nullptr)
{
	MyString obj(ptr);
	return obj;
}
MyString Gun123(const char* ptr = nullptr)
{
	return MyString(ptr);
}

void Foo(const char* ptr = nullptr)
{
	throw MyString(ptr);
}

int main()
{
	MyString abc("abc");

	// 2. 함수가 클래스의 인스턴스를 지역 변수로 만들어 사용한 다음에 값으로
	//    객체를 반환하는 경우에 복사 생성자 또는 이동 생성자의 호출이 생략된다.
	MyString obj1(Fun123("Fun123()"));

	// 3. 함수가 다음과 같이 무명 클래스의 인스턴스를 생성하여 반환하는 경우에
	//    복사 생성자 또는 이동 생성자의 호출이 생략된다.
	MyString obj2(Gun123("Gun123()"));

	// 1. 초기화 리스트를 사용하여 객체를 생성하는 경우에 이동 생성자가 생략된다.
	MyString xyz = "Return Value Optimization";

	std::cout << "복사 생성자, 이동 생성자, 이동 대입 연산자 불린 횟수 : " << Count << std::endl;
}

Constructor : abc
Constructor : Fun123()
Constructor : Gun123()
Constructor : Return Value Optimization
복사 생성자, 이동 생성자, 이동 대입 연산자 불린 횟수 : 0
Destructor : Return Value Optimization
Destructor : Gun123()
Destructor : Fun123()
Destructor : abc
```

- 복사 이동 생략의 원칙은 순수하게 클래스나 구조체에 국한된 이야기이다.