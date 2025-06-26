# 템플릿 08

- 템플릿 포맷
- 템플릿 매개변수
- 템플릿 특수화
- 타입 특성 클래스 템플릿
- 포워드 참조
- 클래스 템플릿의 상속
- 클래스 템플릿의 내부 클래스
- 마무리

템플릿은 실행 비용보다 전체적으로 프로그램의 크기와 함께 난이도를 줄일 수 있다.

```cpp
template<typename T>
T Min(T a, T b)
{
	return ( a < b ) ? a : b;
}
```

템플릿은 위의 함수 템플릿처럼 데이터 타입을 마치 일반 변수처럼 선언하여 컴파일 시점에 데이터 타입을 확정하는 기능을 제공한다.

### 8 - 01 템플릿의 포맷

```cpp
template <템플릿 매개변수-리스트>
함수 또는 클래스 선언문
```

- 템플릿 매개변수
    - `타입 템플릿 매개변수` : 데이터 타입을 가리키는 매개변수
    - `템플릿 템플릿 매개변수` : template 지정자를 사용하여 또 다른 클래스 템플릿을 가리키는 매개변수
    - `타입이 아닌 템플릿 매개변수` : 배열의 크기를 정하거나 또는 클래스나 함수의 지역 변수를 초기화시키는 목적 그리고 함수의 인수처럼 생성 시점에 데이터를 전달하기 위해 사용하는 매개변수

- C++ 언어에서 제공하는 템플릿의 종류는 다음과 같다.
    - 클래스 템플릿
    
    ```cpp
    template<typename T1>
    class String
    {
    	// 아래는 멤버 템플릿 함수이다.
    	template<typename T2>
    	T1 Compare(const T2& s);
    
    };
    
    template<typename T1> // 클래스 템플릿
    template<typename T2> // 멤버 함수 템플릿
    T1 String<T1>::Compare(const T2& s)
    {
    
    }
    ```
    
    - 함수 템플릿
    
    - 타입 템플릿
    
    ```cpp
    template<class T>
    using ptr = T*; // typedef 도 사용 가능
    
    // 타입 템플릿을 사용하는 방법은 다음과 같다.
    ptr<int> x; // int* x의 선언과 같다.
    ```
    
    - 변수 템플릿
        - 많이 안쓰임
        - 클래스 템플릿 내부 멤버 변수들처럼 전역 변수 템플릿을 사용할 수 있도록 만들어준다.
    
    ```cpp
    template<typename T>
    constexpr T pi = T(3.141592);
    ```
    

- 메타 프로그래밍
    - 프로그램을 일종의 데이터로 간주하고 컴파일 시점에 실행 가능한 프로그램으로 변경시켜 주는 프로그램 기법을 말한다.

- 템플릿 변환
    - 실제 사용 가능한 클래스로 변경하는 과정
    
    ```cpp
    vector<int> vec; <- vector 클래스는 int 타입으로 변환한 뒤 인스턴스 생성
    ```
    

- 클래스 템플릿 → 클래스 템플릿 변환 → 클래스 템플릿의 인스턴스

```cpp
#include <iostream>

// 두 개의 인수 가운데 최소 값을 반환한다.
template<typename T>
T Min(T a, T b)
{
	return (a < b) ? a : b;
}

// class 나 Type 도 가능
template<class Type>
Type Max(Type a, Type b)
{
	return (a > b) ? a : b;
}

int main()
{
	// 컴파일러는 인수를 보고 암시적으로 Max<int>로 인식 
	std::cout << "Max : " << Max(5, 6) << std::endl;

	std::cout << "Min : " << Min(5, 6) << std::endl;
	
	// 명시적
	std::cout << "Max : " << Max<double>(5.3, 5.0) << std::endl;
}
```

- 템플릿 인수는 템플릿으로 선언된 매개변수의 순서와 일치해야 한다. 그러나 만약 Type 템플릿 매개변수에 대해 디폴트 int 템플릿 인수를 정의하였다면 생략할 수 있다.

```cpp
template<class T, class Type = int>
T Max(Type a, Type b)
{
	return a > b ? a : b;
}

int main()
{
	std::cout << "최대값 : " << Max<int>(3, 7.0) << std::endl;
}
```

### 8 - 02 템플릿 매개변수

- 타입 템플릿 매개변수
    - 기본 타입이나 묶음 타입처럼 클래스나 함수에 특정 데이터 타입을 명시하는 목적으로 사용하는 템플릿 매개변수
- 템플릿 템플릿 매개변수
    - 또 다른 클래스 템플릿을 가리키는 템플릿 매개변수
    
    ```cpp
    #include <iostream>
    #include <deque>
    #include <vector>
    
    template<typename T, template<typename ELEM> class CONT = std::deque>
    class Stack
    {
    public:
    	void Push(T const& a)
    	{
    		Elems.push_back(a);
    	}
    	void Pop()
    	{
    		Elems.pop_back();
    	}
    	const T& Top() const
    	{
    		return Elems.back();
    	}
    	bool empty() const
    	{
    		return Elems.empty();
    	}
    
    private:
    	CONT<T> Elems;
    };
    
    int main()
    {
    	// 만약 템플릿 매개변수를 인수로 사용한다면 std::vector 클래스 템플릿을 명시해주어야 한다.
    	Stack<int, std::vector> vStack;
    	vStack.Push(1);
    	vStack.Push(2);
    
    	while (vStack.empty() == false)
    	{
    		std::cout << vStack.Top() << std::endl;
    		vStack.Pop();
    	}
    }
    ```
    
- 타입이 아닌 매개변수
    - 함수의 인수처럼 실제 타입과 데이터를 직접 전달할 필요가 있을 때 사용
    
    ```cpp
    // size 매개변수는 '타입이 아닌 템플릿 매개변수'이다.
    template<class T, int size> 
    class MyFile
    {
    public:
    	MyFile() {}
    
    private:
    	T* FilePos;
    	static int Array[size]; // 타입이 아닌 매개변수를 사용해 배열의 크기를 지정한다.
    };
    ```
    

- 타입 템플릿 매개변수(type template parameter)
    - `typename 식별자`
    - `typename … 식별자`
    - class 또는 typename 지정자는 다음에 오는 문장이 타입 템플릿 매개변수라는 사실을 알려주는 키워드이다. 만약 class 지정자 또는 typename 지정자가 없는 템플릿 매개변수가 있다면, 해당 매개변수는 `‘타입이 아닌 템플릿 매개변수’`로 해석된다.
    
    - 디폴트 데이터 타입
    
    ```cpp
    // Allocator 클래스 템플릿을 선언한다.
    template<typename Type>
    class Allocator
    {
    
    };
    
    // 위의 선언된 클래스 템플릿을 Allocator 매개변수의 디폴트 타입으로 만든다. 만약 템플릿을 디폴트 데이터
    // 타입으로 사용한다면, 다음과 같이 템플릿 변환으로 만들어야 사용이 가능하다.
    template<typename Type, typename allocator = Allocator<Type>>
    class Vector
    {
    
    };
    
    int main()
    {
    	// allocator 매개변수에 대응하는 데이터 타입을 명시하지 않는다면,
    	// allocator 인수의 타입은 자동적으로 allocator<int> 타입이 된다.
    	Vector<int> vec1;
    	Vector<int, double> vec2;
    }
    ```
    

- 함수 오버로딩

```cpp
#include <iostream>

template<typename T>
void print(const T& t)
{
	std::cout << t << std::endl;
}

// 첫 번째 인수는 일반 타입 매개변수를 만들고 두 번째 인수는 가변 매개변수로 만든다.
template<typename First, typename... Rest>
void print(const First& first, const Rest&... rest)
{
	std::cout << first << ", ";
	print(rest...); // 함수의 나머지 인수에 대해 함수를 반복 호출시킨다.
}

int main()
{
	print(1);
	print(10, 20);
	print(100, 200, 300);
	print("First", 2, "Third", 3.115, 15);
}
```

- 함수 인수-팩 확장 (function parameter pack expansion)

```cpp
template<typename... Ts>
void func(Ts... args)
{
	// sizeof... 는 가변 인수의 개수를 변환한다.
	const int size = sizeof...(args) + 2;

	// 가변 인수를 배열로 만든다.
	int res[size] = { 1, args..., 2 };
	std::cout << "size of " << size << std::endl;

	// 범위 기반 for 문 내부에 가변 인수를 사용할 수 있다.
	for (auto i : { args... }) { std::cout << i << " "; }
	std::cout << std::endl;

	// 람다 내 캡처절 또는 인수로 만들어 사용할 수 있다.
	auto lm = [&, args...] { return print(args...); }
	lm();

}
```

- 템플릿 템플릿 매개변수
    - 템플릿 변환이 되기 전의 또 다른 클래스 템플릿을 매개변수로 사용한다.
    
    ```cpp
    template< 템플릿 매개변수-리스트 > class [식별자] [ = 디폴트 클래스 템플릿 ]
    template< 템플릿 매개변수-리스트 > typename [식별자 ] [ = 디폴트 클래스 템플릿 ]
    ```
    
    ```cpp
    #include <iostream>
    #include <vector>
    #include <deque>
    #include <list>
    
    // 아래는 콘솔에 출력을 위한 << 비트 이동 연산자 오버로딩이다. 참고로 연산자 오버로딩은 암시적인
    // 템플릿 변환만이 가능하다.
    template<template<class, class...> class C, typename T, class... Args>
    std::ostream& operator<<(std::ostream& os, const C<T, Args...>& objs)
    {
    	for (auto const& obj : objs)
    	{
    		os << obj << " ";
    	}
    	return os;
    }
    
    // deque 클래스 template<class T, class Allocator = std::allocator<T>> class deque 로 선언되어 있다.
    // 따라서 V 템플릿 템플릿 매개변수를 대신하여 deque 클래스 템플릿을 암시적인 방법으로 사용하고 자
    // 한다면 2개의 템플릿 매개변수를 선언해주어야 한다.
    template<template<class, class> class V, class T, class A>
    void f(V<T, A>& v)
    {
    	for (auto const& Temp : v)
    	{
    		std::cout << Temp << " ";
    	}
    	std::cout << std::endl;
    }
    
    template<template<class> class v, class T>
    void g(v<T>& v)
    {
    	while (!v.empty())
    	{
    		T temp = v.back();
    		v.pop_back();
    		std::cout << temp << " ";
    	}
    	std::cout << std::endl;
    }
    
    int main()
    {
    	std::vector<double> vf{ 1.1, 2.2, 3.3, 4.4 };
    	// 연산자 오버로딩에 대해 명시적 템플릿 변환을 적용하고 자 한다면 에러가 발생한다.
    	std::cout << vf << std::endl;
    
    	std::deque<int> di{ 1,2,3,4 };
    	f(di);
    	std::list<char> lc{ 'a','b','c','d' };
    	f<std::list, char>(lc);
    
    	//g(di); //암시적 템플릿 변환을 사용하고 자 한다면 에러가 발생한다.
    	g<std::deque, int>(di);
    	return 0;
    }
    ```
    
    ```cpp
    #include <string>
    #include <iostream>
    
    // 타입 템플릿 매개변수를 사용하여 템플릿 클래스를 선언한다.
    template<typename T>
    struct My_Map
    {
    public:
    	My_Map(T t) : Data(t) {}
    	T GetData() { return Data; }
    
    private:
    	T Data;
    };
    
    // 타입 템플릿 매개변수와 템플릿 템플릿 매개변수를 다음과 같이 선언한다.
    template<typename K, typename V, template<typename T> typename C = My_Map>
    class Map
    {
    public:
    	Map(K k, V v) : Key(k), Value(v) {}
    
    	K GetKey() { return Key.GetData(); }
    	V GetValue() { return Value.GetData(); }
    
    private:
    	C<K> Key;
    	C<V> Value;
    };
    
    int main()
    {
    	Map<int, std::string, My_Map> map(1000, "템플릿 템플릿 인수");
    	std::cout << "Map( " << map.GetKey() << ", " << map.GetValue() << " )\n";
    }
    ```
    
    - 위의 프로그램을 보면, 클래스 템플릿의 매개변수로 my_map 클래스 템플릿을 사용하는 것을 전제로 프로그램되어 있다. 따라서 위의 Map 클래스 템플릿은 GetData() 함수를 가지지 않는 다른 클래스 템플릿을 매개변수로 사용할 수 없다.

- 타입이 아닌 템플릿 매개변수(non-type template parameter)
    - 구체적으로 명시한 데이터 타입과 그에 대응되는 인수
    
    ```cpp
    #include <cstring>
    #include <iostream>
    
    // 아래 'int i'처럼 타입이 아닌 템플릿 매개변수는 타입을 나타내는 class나 typename의 지정자를
    // 사용하지 않는다.
    template<int i>
    class A
    {
    public:
    	A() { memset(Array, 0, i * sizeof(int)); }
    	void Print()
    	{
    		//템플릿 인수는 상수처럼 사용할 수 있다.
    		std::cout << "size of " << i << std::endl;
    		for (auto l : Array) { std::cout << l << std::endl; }
    		std::cout << std::endl;
    	}
    
    private:
    	int Array[i]; //배열의 크기를 템플릿 인수로 제공한다.
    	const int Length = i; //배열의 크기를 상수로 사용한다.
    };
    
    int main()
    {
    	//명시적인 방법으로 템플릿 인수의 값을 10으로 할당하였다. 객체 생성과 함께 내부에 10의 크기를
    	//갖는 배열이 생성된다.
    	A<10> a;
    	a.Print();
    }
    ```
    
    - 템플릿 변환 시 마치 템플릿 인수를 상수처럼 사용한다.
    
    ```cpp
    #include <iostream>
    
    // 타입이 아닌 템플릿 매개변수를 참조로 사용한다.
    template<int& ri>
    struct Simple
    {
    	Simple()
    	{
    		printf("객체 생성 시 ri는 %d 이다.\n", ri);
    	}
    	~Simple()
    	{
    		printf("객체 소멸 시 ri는 %d 이다.\n", ri);
    	}
    };
    
    int i = 1;
    
    int main()
    {
    	// 반드시 전역 변수를 사용하여 객체를 생성해야 한다. 만약 지역 변수를 사용한다면, 컴파일 시점에
    	// 데이터를 확정하지 못해 에러가 발생한다.
    	Simple<i> S;
    	i = 0;
    	return 0;
    }
    
    실행결과
    객체 생성 시 ri는 1 이다.
    객체 소멸 시 ri는 0 이다.
    ```
    
    - 템플릿 인수로 리터럴이 아닌 수정 가능한 클래스나 구조체의 인스턴스 그리고 실수는 허용되지 않는다.
    - 결론은 컴파일 타임에 확정된 리터럴을 집어 넣을 수 있다는 것인듯

### 8 - 03 템플릿 특수화

- 템플릿 특수화(Template Specialization) 는 다음과 같이 클래스 템플릿 또는 함수 템플릿을 선언한 이후에 예외의 대상이 되는 특정 데이터 타입을 미리 템플릿 인수로 지정하는 것을 말한다.

```cpp
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

// 클래스 템플릿을 선언하거나 정의한다.
template<typename T>
inline std::string Stringify(T const& x)
{
	std::ostringstream out;
	out << x;
	return out.str();
}

// 아래는 전체 템플릿 특수화로 별도 템플릿 매개변수를 지정하지 않는다. 그리고 템플릿 인수를 지정하여
// 위의 템플릿 매개변수와 또 다른 형식의 함수 오버로딩처럼 사용한다.
template<>
inline std::string Stringify<bool>(bool const& x)
{
	std::ostringstream out;
	out << std::boolalpha << x;
	return out.str();
}

template<>
inline std::string Stringify<double>(double const& x)
{
	std::ostringstream out;
	const int Sigdigits = std::numeric_limits<double>::digits10;
	out << std::setprecision(Sigdigits) << x;
	return out.str();
}

int main()
{
	std::cout << Stringify<int>(100) << ", " << Stringify<bool>(true) << ", " <<
		Stringify<double>(23.65) << std::endl;
}
```

- 전체 템플릿 특수화(Explicit Full Template Specialization)
    - 템플릿에서 선언한 템플릿 매개변수 전체에 대해 특정 데이터 타입으로 템플릿 인수를 지정하는 경우를 말한다.
- 부분 템플릿 특수화(Partial Template Specialization)
    - 템플릿에서 선언한 템플릿 매개변수 가운데 일부에 대해 특정 데이터 타입으로 템플릿 인수를 지정하는 경우를 말한다.

- 전체 템플릿 특수화

```cpp
#include <iostream>

template<class T>
class Form
{
public:
	Form(T* t) : _t(t) {}
	void Print()
	{
		std::cout << *_t << std::endl;
	}

private:
	T* _t;
};

// 아래와 같이 char* 타입을 사용하여 템플릿 변환을 적용한다면, 변환 인수로
// 사용한 데이터 타입에 대해 아래 템플릿이 위의 템플릿보다 우선적으로 적용된다.
template<>
class Form<char*>
{
public:
	Form(char* t) : _t(t) {}
	void Print()
	{
		std::cout << "Form<char*> : " << _t << std::endl;
	}

private:
	char* _t;
};

int main()
{
	int i = 157;
	Form<int> form1(&i); // 기본 템플릿을 적용한다.

	char c[10] = "string1";
	// char* 인수를 사용하여 템플릿 특수화된 클래스 템플릿의 인스턴스를 만든다.
	Form<char*> form2(c);

	form1.Print();
	form2.Print();
}
```

### 8 - 04 타입 특성 클래스 템플릿

- 컴파일러에 타입 정보를 제공해 주는 특수 목적의 클래스 템플릿을 말함

- 아래 함수 템플릿의 경우, 만약 int* 처럼 포인터를 사용한다면, 함수 템플릿은 템플릿 변환후 실행하는 과정에서 예상치 못한 에러가 발생하게 된다.

```cpp
#include <iostream>

template<class T>
T Min(T a, T b)
{
	return (a < b) ? a : b;
}

int main()
{
	int tmp01 = 10;
	int tmp02 = 20;
	int* a = &tmp01, *b = &tmp02;

	std::cout << "1. 최솟값 : " << Min(*a, *b) << std::endl;
	std::cout << "2. 최솟값 : " << Min<int*>(a, b) << std::endl;
}
```

- 대부분 크게 기본 템플릿이나 포인터에 대한 템플릿을 만들어 사용한다.

- enable_if 구조체 템플릿은 bool 타입의 true 또는 false 에 따라 다른 클래스 템플릿 또는 함수 템플릿에 대한 활성화 또는 비활성화시키는 용도로 사용한다.

```cpp
#include <iostream>
#include <type_traits>
#include <string>

using namespace std;

// 템플릿 인수가 lvalue 참조가 아니라면, 아래 함수 템플릿을 활성화시킨다.
template<class T>
typename std::enable_if<!std::is_lvalue_reference<T>::value, T&>::type min(T& a, T& b)
{
	std::cout << "변 수";
	return (a < b) ? a : b;
}

// 템플릿 인수가 lvalue 참고이라면 아래 함수 템플릿을 활성화시킨다.
template<class T>
typename std::enable_if<std::is_lvalue_reference<T>::value, T>::type min(T a, T b)
{
	std::cout << "참 조";
	return (a < b) ? a : b;
}

// 템플릿 인수가 포인터라면 아래 함수 템플릿을 활성화시킨다.
template<class T>
T min(T* a, T* b)
{
	std::cout << "포인터";
	return (*a < *b) ? *a : *b;
}

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

bool operator<(Shape& a, Shape& b)
{
	return a.GetArea() < b.GetArea();
}

bool operator>(Shape& a, Shape& b)
{
	return a.GetArea() > b.GetArea();
}

int main()
{
	int tmp01 = 10;
	int tmp02 = 20;
	int& tmp03 = tmp01;
	int& tmp04 = tmp02;
	int* a = &tmp01, *b = &tmp02;
	std::cout << "1. 최솟값 : " << min<int>(*a, *b) << std::endl;
	std::cout << "2. 최솟값 : " << min<int&>(tmp03, tmp04) << std::endl;
	std::cout << "3. 최솟값 : " << min(a, b) << std::endl;

	Rectangle shape01 = Rectangle("직사각형", 10, 5);
	Circle shape02 = Circle(10);
	std::cout << "4. 최솟값 : ";
	Shape& s1 = min<Shape&>(shape01, shape02);
	s1.GetArea();

	std::cout << "5. 최솟값 : ";
	Shape& s2 = min<Shape>(shape01, shape02);
	s2.GetArea();

	return 0;
}
```

- `std::is_lvalue_reference<T>::value, T&>::type`
    - T 타입이 lvalue 참조냐 아니냐에 따라 활성화 또는 비활성화가 결정됨
    - 이러한 데이터 타입을 `의존 타입`이라 함
- 의존 타입
    - 컴파일하는 과정에서 조건이 맞지 않는다면 컴파일되지 않는 특징이 있음
    - ‘typename’ 지정자를 사용하여 반환되는 함수의 데이터 타입이 의존 타입이란 사실을 명시해 주어야 한다.

### 8 - 05 포워드 참조

```cpp
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
```

### 8 - 08 마무리

- 요점 정리
    - 템플릿은 함수나 클래스를 생성하기 위한 템플릿 메타프로그래밍을 의미하며 실제 함수나 클래스를 의미하지 않는다. 따라서 템플릿에 대한 인스턴스화하는 과정은 다음과 같다.
        - `템플릿 클래스 → 템플릿 변환 → 템플릿 인스턴스화`
    - 템플릿 변환으로 인해 동일한 함수와 클래스가 생성되지 않는다면, 하나 이상의 템플릿을 선언하더라도 아무런 문제가 되지 않는다.
    
    - 기본 템플릿에 적용할 수 없는 타입이 존재한다면, 다음과 같은 방법을 사용할 수 있다.
        - 템플릿 특수화는 예외의 대상이 되는 특정 데이터 타입에 대한 템플릿 변환을 수행한다.
        - 타입 특성 클래스 템플릿 가운데 enable_if 구조체 템플릿을 사용하여 템플릿을 활성화하거나 또는 비활성화시키는 방법을 사용한다.

# 템플릿 08

- 템플릿 포맷
- 템플릿 매개변수
- 템플릿 특수화
- 타입 특성 클래스 템플릿
- 포워드 참조
- 클래스 템플릿의 상속
- 클래스 템플릿의 내부 클래스
- 마무리

템플릿은 실행 비용보다 전체적으로 프로그램의 크기와 함께 난이도를 줄일 수 있다.

```cpp
template<typename T>
T Min(T a, T b)
{
	return ( a < b ) ? a : b;
}
```

템플릿은 위의 함수 템플릿처럼 데이터 타입을 마치 일반 변수처럼 선언하여 컴파일 시점에 데이터 타입을 확정하는 기능을 제공한다.

### 8 - 01 템플릿의 포맷

```cpp
template <템플릿 매개변수-리스트>
함수 또는 클래스 선언문
```

- 템플릿 매개변수
    - `타입 템플릿 매개변수` : 데이터 타입을 가리키는 매개변수
    - `템플릿 템플릿 매개변수` : template 지정자를 사용하여 또 다른 클래스 템플릿을 가리키는 매개변수
    - `타입이 아닌 템플릿 매개변수` : 배열의 크기를 정하거나 또는 클래스나 함수의 지역 변수를 초기화시키는 목적 그리고 함수의 인수처럼 생성 시점에 데이터를 전달하기 위해 사용하는 매개변수

- C++ 언어에서 제공하는 템플릿의 종류는 다음과 같다.
    - 클래스 템플릿
    
    ```cpp
    template<typename T1>
    class String
    {
    	// 아래는 멤버 템플릿 함수이다.
    	template<typename T2>
    	T1 Compare(const T2& s);
    
    };
    
    template<typename T1> // 클래스 템플릿
    template<typename T2> // 멤버 함수 템플릿
    T1 String<T1>::Compare(const T2& s)
    {
    
    }
    ```
    
    - 함수 템플릿
    
    - 타입 템플릿
    
    ```cpp
    template<class T>
    using ptr = T*; // typedef 도 사용 가능
    
    // 타입 템플릿을 사용하는 방법은 다음과 같다.
    ptr<int> x; // int* x의 선언과 같다.
    ```
    
    - 변수 템플릿
        - 많이 안쓰임
        - 클래스 템플릿 내부 멤버 변수들처럼 전역 변수 템플릿을 사용할 수 있도록 만들어준다.
    
    ```cpp
    template<typename T>
    constexpr T pi = T(3.141592);
    ```
    

- 메타 프로그래밍
    - 프로그램을 일종의 데이터로 간주하고 컴파일 시점에 실행 가능한 프로그램으로 변경시켜 주는 프로그램 기법을 말한다.

- 템플릿 변환
    - 실제 사용 가능한 클래스로 변경하는 과정
    
    ```cpp
    vector<int> vec; <- vector 클래스는 int 타입으로 변환한 뒤 인스턴스 생성
    ```
    

- 클래스 템플릿 → 클래스 템플릿 변환 → 클래스 템플릿의 인스턴스

```cpp
#include <iostream>

// 두 개의 인수 가운데 최소 값을 반환한다.
template<typename T>
T Min(T a, T b)
{
	return (a < b) ? a : b;
}

// class 나 Type 도 가능
template<class Type>
Type Max(Type a, Type b)
{
	return (a > b) ? a : b;
}

int main()
{
	// 컴파일러는 인수를 보고 암시적으로 Max<int>로 인식 
	std::cout << "Max : " << Max(5, 6) << std::endl;

	std::cout << "Min : " << Min(5, 6) << std::endl;
	
	// 명시적
	std::cout << "Max : " << Max<double>(5.3, 5.0) << std::endl;
}
```

- 템플릿 인수는 템플릿으로 선언된 매개변수의 순서와 일치해야 한다. 그러나 만약 Type 템플릿 매개변수에 대해 디폴트 int 템플릿 인수를 정의하였다면 생략할 수 있다.

```cpp
template<class T, class Type = int>
T Max(Type a, Type b)
{
	return a > b ? a : b;
}

int main()
{
	std::cout << "최대값 : " << Max<int>(3, 7.0) << std::endl;
}
```

### 8 - 02 템플릿 매개변수

- 타입 템플릿 매개변수
    - 기본 타입이나 묶음 타입처럼 클래스나 함수에 특정 데이터 타입을 명시하는 목적으로 사용하는 템플릿 매개변수
- 템플릿 템플릿 매개변수
    - 또 다른 클래스 템플릿을 가리키는 템플릿 매개변수
    
    ```cpp
    #include <iostream>
    #include <deque>
    #include <vector>
    
    template<typename T, template<typename ELEM> class CONT = std::deque>
    class Stack
    {
    public:
    	void Push(T const& a)
    	{
    		Elems.push_back(a);
    	}
    	void Pop()
    	{
    		Elems.pop_back();
    	}
    	const T& Top() const
    	{
    		return Elems.back();
    	}
    	bool empty() const
    	{
    		return Elems.empty();
    	}
    
    private:
    	CONT<T> Elems;
    };
    
    int main()
    {
    	// 만약 템플릿 매개변수를 인수로 사용한다면 std::vector 클래스 템플릿을 명시해주어야 한다.
    	Stack<int, std::vector> vStack;
    	vStack.Push(1);
    	vStack.Push(2);
    
    	while (vStack.empty() == false)
    	{
    		std::cout << vStack.Top() << std::endl;
    		vStack.Pop();
    	}
    }
    ```
    
- 타입이 아닌 매개변수
    - 함수의 인수처럼 실제 타입과 데이터를 직접 전달할 필요가 있을 때 사용
    
    ```cpp
    // size 매개변수는 '타입이 아닌 템플릿 매개변수'이다.
    template<class T, int size> 
    class MyFile
    {
    public:
    	MyFile() {}
    
    private:
    	T* FilePos;
    	static int Array[size]; // 타입이 아닌 매개변수를 사용해 배열의 크기를 지정한다.
    };
    ```
    

- 타입 템플릿 매개변수(type template parameter)
    - `typename 식별자`
    - `typename … 식별자`
    - class 또는 typename 지정자는 다음에 오는 문장이 타입 템플릿 매개변수라는 사실을 알려주는 키워드이다. 만약 class 지정자 또는 typename 지정자가 없는 템플릿 매개변수가 있다면, 해당 매개변수는 `‘타입이 아닌 템플릿 매개변수’`로 해석된다.
    
    - 디폴트 데이터 타입
    
    ```cpp
    // Allocator 클래스 템플릿을 선언한다.
    template<typename Type>
    class Allocator
    {
    
    };
    
    // 위의 선언된 클래스 템플릿을 Allocator 매개변수의 디폴트 타입으로 만든다. 만약 템플릿을 디폴트 데이터
    // 타입으로 사용한다면, 다음과 같이 템플릿 변환으로 만들어야 사용이 가능하다.
    template<typename Type, typename allocator = Allocator<Type>>
    class Vector
    {
    
    };
    
    int main()
    {
    	// allocator 매개변수에 대응하는 데이터 타입을 명시하지 않는다면,
    	// allocator 인수의 타입은 자동적으로 allocator<int> 타입이 된다.
    	Vector<int> vec1;
    	Vector<int, double> vec2;
    }
    ```
    

- 함수 오버로딩

```cpp
#include <iostream>

template<typename T>
void print(const T& t)
{
	std::cout << t << std::endl;
}

// 첫 번째 인수는 일반 타입 매개변수를 만들고 두 번째 인수는 가변 매개변수로 만든다.
template<typename First, typename... Rest>
void print(const First& first, const Rest&... rest)
{
	std::cout << first << ", ";
	print(rest...); // 함수의 나머지 인수에 대해 함수를 반복 호출시킨다.
}

int main()
{
	print(1);
	print(10, 20);
	print(100, 200, 300);
	print("First", 2, "Third", 3.115, 15);
}
```

- 함수 인수-팩 확장 (function parameter pack expansion)

```cpp
template<typename... Ts>
void func(Ts... args)
{
	// sizeof... 는 가변 인수의 개수를 변환한다.
	const int size = sizeof...(args) + 2;

	// 가변 인수를 배열로 만든다.
	int res[size] = { 1, args..., 2 };
	std::cout << "size of " << size << std::endl;

	// 범위 기반 for 문 내부에 가변 인수를 사용할 수 있다.
	for (auto i : { args... }) { std::cout << i << " "; }
	std::cout << std::endl;

	// 람다 내 캡처절 또는 인수로 만들어 사용할 수 있다.
	auto lm = [&, args...] { return print(args...); }
	lm();

}
```

- 템플릿 템플릿 매개변수
    - 템플릿 변환이 되기 전의 또 다른 클래스 템플릿을 매개변수로 사용한다.
    
    ```cpp
    template< 템플릿 매개변수-리스트 > class [식별자] [ = 디폴트 클래스 템플릿 ]
    template< 템플릿 매개변수-리스트 > typename [식별자 ] [ = 디폴트 클래스 템플릿 ]
    ```
    
    ```cpp
    #include <iostream>
    #include <vector>
    #include <deque>
    #include <list>
    
    // 아래는 콘솔에 출력을 위한 << 비트 이동 연산자 오버로딩이다. 참고로 연산자 오버로딩은 암시적인
    // 템플릿 변환만이 가능하다.
    template<template<class, class...> class C, typename T, class... Args>
    std::ostream& operator<<(std::ostream& os, const C<T, Args...>& objs)
    {
    	for (auto const& obj : objs)
    	{
    		os << obj << " ";
    	}
    	return os;
    }
    
    // deque 클래스 template<class T, class Allocator = std::allocator<T>> class deque 로 선언되어 있다.
    // 따라서 V 템플릿 템플릿 매개변수를 대신하여 deque 클래스 템플릿을 암시적인 방법으로 사용하고 자
    // 한다면 2개의 템플릿 매개변수를 선언해주어야 한다.
    template<template<class, class> class V, class T, class A>
    void f(V<T, A>& v)
    {
    	for (auto const& Temp : v)
    	{
    		std::cout << Temp << " ";
    	}
    	std::cout << std::endl;
    }
    
    template<template<class> class v, class T>
    void g(v<T>& v)
    {
    	while (!v.empty())
    	{
    		T temp = v.back();
    		v.pop_back();
    		std::cout << temp << " ";
    	}
    	std::cout << std::endl;
    }
    
    int main()
    {
    	std::vector<double> vf{ 1.1, 2.2, 3.3, 4.4 };
    	// 연산자 오버로딩에 대해 명시적 템플릿 변환을 적용하고 자 한다면 에러가 발생한다.
    	std::cout << vf << std::endl;
    
    	std::deque<int> di{ 1,2,3,4 };
    	f(di);
    	std::list<char> lc{ 'a','b','c','d' };
    	f<std::list, char>(lc);
    
    	//g(di); //암시적 템플릿 변환을 사용하고 자 한다면 에러가 발생한다.
    	g<std::deque, int>(di);
    	return 0;
    }
    ```
    
    ```cpp
    #include <string>
    #include <iostream>
    
    // 타입 템플릿 매개변수를 사용하여 템플릿 클래스를 선언한다.
    template<typename T>
    struct My_Map
    {
    public:
    	My_Map(T t) : Data(t) {}
    	T GetData() { return Data; }
    
    private:
    	T Data;
    };
    
    // 타입 템플릿 매개변수와 템플릿 템플릿 매개변수를 다음과 같이 선언한다.
    template<typename K, typename V, template<typename T> typename C = My_Map>
    class Map
    {
    public:
    	Map(K k, V v) : Key(k), Value(v) {}
    
    	K GetKey() { return Key.GetData(); }
    	V GetValue() { return Value.GetData(); }
    
    private:
    	C<K> Key;
    	C<V> Value;
    };
    
    int main()
    {
    	Map<int, std::string, My_Map> map(1000, "템플릿 템플릿 인수");
    	std::cout << "Map( " << map.GetKey() << ", " << map.GetValue() << " )\n";
    }
    ```
    
    - 위의 프로그램을 보면, 클래스 템플릿의 매개변수로 my_map 클래스 템플릿을 사용하는 것을 전제로 프로그램되어 있다. 따라서 위의 Map 클래스 템플릿은 GetData() 함수를 가지지 않는 다른 클래스 템플릿을 매개변수로 사용할 수 없다.

- 타입이 아닌 템플릿 매개변수(non-type template parameter)
    - 구체적으로 명시한 데이터 타입과 그에 대응되는 인수
    
    ```cpp
    #include <cstring>
    #include <iostream>
    
    // 아래 'int i'처럼 타입이 아닌 템플릿 매개변수는 타입을 나타내는 class나 typename의 지정자를
    // 사용하지 않는다.
    template<int i>
    class A
    {
    public:
    	A() { memset(Array, 0, i * sizeof(int)); }
    	void Print()
    	{
    		//템플릿 인수는 상수처럼 사용할 수 있다.
    		std::cout << "size of " << i << std::endl;
    		for (auto l : Array) { std::cout << l << std::endl; }
    		std::cout << std::endl;
    	}
    
    private:
    	int Array[i]; //배열의 크기를 템플릿 인수로 제공한다.
    	const int Length = i; //배열의 크기를 상수로 사용한다.
    };
    
    int main()
    {
    	//명시적인 방법으로 템플릿 인수의 값을 10으로 할당하였다. 객체 생성과 함께 내부에 10의 크기를
    	//갖는 배열이 생성된다.
    	A<10> a;
    	a.Print();
    }
    ```
    
    - 템플릿 변환 시 마치 템플릿 인수를 상수처럼 사용한다.
    
    ```cpp
    #include <iostream>
    
    // 타입이 아닌 템플릿 매개변수를 참조로 사용한다.
    template<int& ri>
    struct Simple
    {
    	Simple()
    	{
    		printf("객체 생성 시 ri는 %d 이다.\n", ri);
    	}
    	~Simple()
    	{
    		printf("객체 소멸 시 ri는 %d 이다.\n", ri);
    	}
    };
    
    int i = 1;
    
    int main()
    {
    	// 반드시 전역 변수를 사용하여 객체를 생성해야 한다. 만약 지역 변수를 사용한다면, 컴파일 시점에
    	// 데이터를 확정하지 못해 에러가 발생한다.
    	Simple<i> S;
    	i = 0;
    	return 0;
    }
    
    실행결과
    객체 생성 시 ri는 1 이다.
    객체 소멸 시 ri는 0 이다.
    ```
    
    - 템플릿 인수로 리터럴이 아닌 수정 가능한 클래스나 구조체의 인스턴스 그리고 실수는 허용되지 않는다.
    - 결론은 컴파일 타임에 확정된 리터럴을 집어 넣을 수 있다는 것인듯

### 8 - 03 템플릿 특수화

- 템플릿 특수화(Template Specialization) 는 다음과 같이 클래스 템플릿 또는 함수 템플릿을 선언한 이후에 예외의 대상이 되는 특정 데이터 타입을 미리 템플릿 인수로 지정하는 것을 말한다.

```cpp
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

// 클래스 템플릿을 선언하거나 정의한다.
template<typename T>
inline std::string Stringify(T const& x)
{
	std::ostringstream out;
	out << x;
	return out.str();
}

// 아래는 전체 템플릿 특수화로 별도 템플릿 매개변수를 지정하지 않는다. 그리고 템플릿 인수를 지정하여
// 위의 템플릿 매개변수와 또 다른 형식의 함수 오버로딩처럼 사용한다.
template<>
inline std::string Stringify<bool>(bool const& x)
{
	std::ostringstream out;
	out << std::boolalpha << x;
	return out.str();
}

template<>
inline std::string Stringify<double>(double const& x)
{
	std::ostringstream out;
	const int Sigdigits = std::numeric_limits<double>::digits10;
	out << std::setprecision(Sigdigits) << x;
	return out.str();
}

int main()
{
	std::cout << Stringify<int>(100) << ", " << Stringify<bool>(true) << ", " <<
		Stringify<double>(23.65) << std::endl;
}
```

- 전체 템플릿 특수화(Explicit Full Template Specialization)
    - 템플릿에서 선언한 템플릿 매개변수 전체에 대해 특정 데이터 타입으로 템플릿 인수를 지정하는 경우를 말한다.
- 부분 템플릿 특수화(Partial Template Specialization)
    - 템플릿에서 선언한 템플릿 매개변수 가운데 일부에 대해 특정 데이터 타입으로 템플릿 인수를 지정하는 경우를 말한다.

- 전체 템플릿 특수화

```cpp
#include <iostream>

template<class T>
class Form
{
public:
	Form(T* t) : _t(t) {}
	void Print()
	{
		std::cout << *_t << std::endl;
	}

private:
	T* _t;
};

// 아래와 같이 char* 타입을 사용하여 템플릿 변환을 적용한다면, 변환 인수로
// 사용한 데이터 타입에 대해 아래 템플릿이 위의 템플릿보다 우선적으로 적용된다.
template<>
class Form<char*>
{
public:
	Form(char* t) : _t(t) {}
	void Print()
	{
		std::cout << "Form<char*> : " << _t << std::endl;
	}

private:
	char* _t;
};

int main()
{
	int i = 157;
	Form<int> form1(&i); // 기본 템플릿을 적용한다.

	char c[10] = "string1";
	// char* 인수를 사용하여 템플릿 특수화된 클래스 템플릿의 인스턴스를 만든다.
	Form<char*> form2(c);

	form1.Print();
	form2.Print();
}
```

### 8 - 04 타입 특성 클래스 템플릿

- 컴파일러에 타입 정보를 제공해 주는 특수 목적의 클래스 템플릿을 말함

- 아래 함수 템플릿의 경우, 만약 int* 처럼 포인터를 사용한다면, 함수 템플릿은 템플릿 변환후 실행하는 과정에서 예상치 못한 에러가 발생하게 된다.

```cpp
#include <iostream>

template<class T>
T Min(T a, T b)
{
	return (a < b) ? a : b;
}

int main()
{
	int tmp01 = 10;
	int tmp02 = 20;
	int* a = &tmp01, *b = &tmp02;

	std::cout << "1. 최솟값 : " << Min(*a, *b) << std::endl;
	std::cout << "2. 최솟값 : " << Min<int*>(a, b) << std::endl;
}
```

- 대부분 크게 기본 템플릿이나 포인터에 대한 템플릿을 만들어 사용한다.

- enable_if 구조체 템플릿은 bool 타입의 true 또는 false 에 따라 다른 클래스 템플릿 또는 함수 템플릿에 대한 활성화 또는 비활성화시키는 용도로 사용한다.

```cpp
#include <iostream>
#include <type_traits>
#include <string>

using namespace std;

// 템플릿 인수가 lvalue 참조가 아니라면, 아래 함수 템플릿을 활성화시킨다.
template<class T>
typename std::enable_if<!std::is_lvalue_reference<T>::value, T&>::type min(T& a, T& b)
{
	std::cout << "변 수";
	return (a < b) ? a : b;
}

// 템플릿 인수가 lvalue 참고이라면 아래 함수 템플릿을 활성화시킨다.
template<class T>
typename std::enable_if<std::is_lvalue_reference<T>::value, T>::type min(T a, T b)
{
	std::cout << "참 조";
	return (a < b) ? a : b;
}

// 템플릿 인수가 포인터라면 아래 함수 템플릿을 활성화시킨다.
template<class T>
T min(T* a, T* b)
{
	std::cout << "포인터";
	return (*a < *b) ? *a : *b;
}

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

bool operator<(Shape& a, Shape& b)
{
	return a.GetArea() < b.GetArea();
}

bool operator>(Shape& a, Shape& b)
{
	return a.GetArea() > b.GetArea();
}

int main()
{
	int tmp01 = 10;
	int tmp02 = 20;
	int& tmp03 = tmp01;
	int& tmp04 = tmp02;
	int* a = &tmp01, *b = &tmp02;
	std::cout << "1. 최솟값 : " << min<int>(*a, *b) << std::endl;
	std::cout << "2. 최솟값 : " << min<int&>(tmp03, tmp04) << std::endl;
	std::cout << "3. 최솟값 : " << min(a, b) << std::endl;

	Rectangle shape01 = Rectangle("직사각형", 10, 5);
	Circle shape02 = Circle(10);
	std::cout << "4. 최솟값 : ";
	Shape& s1 = min<Shape&>(shape01, shape02);
	s1.GetArea();

	std::cout << "5. 최솟값 : ";
	Shape& s2 = min<Shape>(shape01, shape02);
	s2.GetArea();

	return 0;
}
```

- `std::is_lvalue_reference<T>::value, T&>::type`
    - T 타입이 lvalue 참조냐 아니냐에 따라 활성화 또는 비활성화가 결정됨
    - 이러한 데이터 타입을 `의존 타입`이라 함
- 의존 타입
    - 컴파일하는 과정에서 조건이 맞지 않는다면 컴파일되지 않는 특징이 있음
    - ‘typename’ 지정자를 사용하여 반환되는 함수의 데이터 타입이 의존 타입이란 사실을 명시해 주어야 한다.

### 8 - 05 포워드 참조

```cpp
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
```

### 8 - 08 마무리

- 요점 정리
    - 템플릿은 함수나 클래스를 생성하기 위한 템플릿 메타프로그래밍을 의미하며 실제 함수나 클래스를 의미하지 않는다. 따라서 템플릿에 대한 인스턴스화하는 과정은 다음과 같다.
        - `템플릿 클래스 → 템플릿 변환 → 템플릿 인스턴스화`
    - 템플릿 변환으로 인해 동일한 함수와 클래스가 생성되지 않는다면, 하나 이상의 템플릿을 선언하더라도 아무런 문제가 되지 않는다.
    
    - 기본 템플릿에 적용할 수 없는 타입이 존재한다면, 다음과 같은 방법을 사용할 수 있다.
        - 템플릿 특수화는 예외의 대상이 되는 특정 데이터 타입에 대한 템플릿 변환을 수행한다.
        - 타입 특성 클래스 템플릿 가운데 enable_if 구조체 템플릿을 사용하여 템플릿을 활성화하거나 또는 비활성화시키는 방법을 사용한다.

# 템플릿 08

- 템플릿 포맷
- 템플릿 매개변수
- 템플릿 특수화
- 타입 특성 클래스 템플릿
- 포워드 참조
- 클래스 템플릿의 상속
- 클래스 템플릿의 내부 클래스
- 마무리

템플릿은 실행 비용보다 전체적으로 프로그램의 크기와 함께 난이도를 줄일 수 있다.

```cpp
template<typename T>
T Min(T a, T b)
{
	return ( a < b ) ? a : b;
}
```

템플릿은 위의 함수 템플릿처럼 데이터 타입을 마치 일반 변수처럼 선언하여 컴파일 시점에 데이터 타입을 확정하는 기능을 제공한다.

### 8 - 01 템플릿의 포맷

```cpp
template <템플릿 매개변수-리스트>
함수 또는 클래스 선언문
```

- 템플릿 매개변수
    - `타입 템플릿 매개변수` : 데이터 타입을 가리키는 매개변수
    - `템플릿 템플릿 매개변수` : template 지정자를 사용하여 또 다른 클래스 템플릿을 가리키는 매개변수
    - `타입이 아닌 템플릿 매개변수` : 배열의 크기를 정하거나 또는 클래스나 함수의 지역 변수를 초기화시키는 목적 그리고 함수의 인수처럼 생성 시점에 데이터를 전달하기 위해 사용하는 매개변수

- C++ 언어에서 제공하는 템플릿의 종류는 다음과 같다.
    - 클래스 템플릿
    
    ```cpp
    template<typename T1>
    class String
    {
    	// 아래는 멤버 템플릿 함수이다.
    	template<typename T2>
    	T1 Compare(const T2& s);
    
    };
    
    template<typename T1> // 클래스 템플릿
    template<typename T2> // 멤버 함수 템플릿
    T1 String<T1>::Compare(const T2& s)
    {
    
    }
    ```
    
    - 함수 템플릿
    
    - 타입 템플릿
    
    ```cpp
    template<class T>
    using ptr = T*; // typedef 도 사용 가능
    
    // 타입 템플릿을 사용하는 방법은 다음과 같다.
    ptr<int> x; // int* x의 선언과 같다.
    ```
    
    - 변수 템플릿
        - 많이 안쓰임
        - 클래스 템플릿 내부 멤버 변수들처럼 전역 변수 템플릿을 사용할 수 있도록 만들어준다.
    
    ```cpp
    template<typename T>
    constexpr T pi = T(3.141592);
    ```
    

- 메타 프로그래밍
    - 프로그램을 일종의 데이터로 간주하고 컴파일 시점에 실행 가능한 프로그램으로 변경시켜 주는 프로그램 기법을 말한다.

- 템플릿 변환
    - 실제 사용 가능한 클래스로 변경하는 과정
    
    ```cpp
    vector<int> vec; <- vector 클래스는 int 타입으로 변환한 뒤 인스턴스 생성
    ```
    

- 클래스 템플릿 → 클래스 템플릿 변환 → 클래스 템플릿의 인스턴스

```cpp
#include <iostream>

// 두 개의 인수 가운데 최소 값을 반환한다.
template<typename T>
T Min(T a, T b)
{
	return (a < b) ? a : b;
}

// class 나 Type 도 가능
template<class Type>
Type Max(Type a, Type b)
{
	return (a > b) ? a : b;
}

int main()
{
	// 컴파일러는 인수를 보고 암시적으로 Max<int>로 인식 
	std::cout << "Max : " << Max(5, 6) << std::endl;

	std::cout << "Min : " << Min(5, 6) << std::endl;
	
	// 명시적
	std::cout << "Max : " << Max<double>(5.3, 5.0) << std::endl;
}
```

- 템플릿 인수는 템플릿으로 선언된 매개변수의 순서와 일치해야 한다. 그러나 만약 Type 템플릿 매개변수에 대해 디폴트 int 템플릿 인수를 정의하였다면 생략할 수 있다.

```cpp
template<class T, class Type = int>
T Max(Type a, Type b)
{
	return a > b ? a : b;
}

int main()
{
	std::cout << "최대값 : " << Max<int>(3, 7.0) << std::endl;
}
```

### 8 - 02 템플릿 매개변수

- 타입 템플릿 매개변수
    - 기본 타입이나 묶음 타입처럼 클래스나 함수에 특정 데이터 타입을 명시하는 목적으로 사용하는 템플릿 매개변수
- 템플릿 템플릿 매개변수
    - 또 다른 클래스 템플릿을 가리키는 템플릿 매개변수
    
    ```cpp
    #include <iostream>
    #include <deque>
    #include <vector>
    
    template<typename T, template<typename ELEM> class CONT = std::deque>
    class Stack
    {
    public:
    	void Push(T const& a)
    	{
    		Elems.push_back(a);
    	}
    	void Pop()
    	{
    		Elems.pop_back();
    	}
    	const T& Top() const
    	{
    		return Elems.back();
    	}
    	bool empty() const
    	{
    		return Elems.empty();
    	}
    
    private:
    	CONT<T> Elems;
    };
    
    int main()
    {
    	// 만약 템플릿 매개변수를 인수로 사용한다면 std::vector 클래스 템플릿을 명시해주어야 한다.
    	Stack<int, std::vector> vStack;
    	vStack.Push(1);
    	vStack.Push(2);
    
    	while (vStack.empty() == false)
    	{
    		std::cout << vStack.Top() << std::endl;
    		vStack.Pop();
    	}
    }
    ```
    
- 타입이 아닌 매개변수
    - 함수의 인수처럼 실제 타입과 데이터를 직접 전달할 필요가 있을 때 사용
    
    ```cpp
    // size 매개변수는 '타입이 아닌 템플릿 매개변수'이다.
    template<class T, int size> 
    class MyFile
    {
    public:
    	MyFile() {}
    
    private:
    	T* FilePos;
    	static int Array[size]; // 타입이 아닌 매개변수를 사용해 배열의 크기를 지정한다.
    };
    ```
    

- 타입 템플릿 매개변수(type template parameter)
    - `typename 식별자`
    - `typename … 식별자`
    - class 또는 typename 지정자는 다음에 오는 문장이 타입 템플릿 매개변수라는 사실을 알려주는 키워드이다. 만약 class 지정자 또는 typename 지정자가 없는 템플릿 매개변수가 있다면, 해당 매개변수는 `‘타입이 아닌 템플릿 매개변수’`로 해석된다.
    
    - 디폴트 데이터 타입
    
    ```cpp
    // Allocator 클래스 템플릿을 선언한다.
    template<typename Type>
    class Allocator
    {
    
    };
    
    // 위의 선언된 클래스 템플릿을 Allocator 매개변수의 디폴트 타입으로 만든다. 만약 템플릿을 디폴트 데이터
    // 타입으로 사용한다면, 다음과 같이 템플릿 변환으로 만들어야 사용이 가능하다.
    template<typename Type, typename allocator = Allocator<Type>>
    class Vector
    {
    
    };
    
    int main()
    {
    	// allocator 매개변수에 대응하는 데이터 타입을 명시하지 않는다면,
    	// allocator 인수의 타입은 자동적으로 allocator<int> 타입이 된다.
    	Vector<int> vec1;
    	Vector<int, double> vec2;
    }
    ```
    

- 함수 오버로딩

```cpp
#include <iostream>

template<typename T>
void print(const T& t)
{
	std::cout << t << std::endl;
}

// 첫 번째 인수는 일반 타입 매개변수를 만들고 두 번째 인수는 가변 매개변수로 만든다.
template<typename First, typename... Rest>
void print(const First& first, const Rest&... rest)
{
	std::cout << first << ", ";
	print(rest...); // 함수의 나머지 인수에 대해 함수를 반복 호출시킨다.
}

int main()
{
	print(1);
	print(10, 20);
	print(100, 200, 300);
	print("First", 2, "Third", 3.115, 15);
}
```

- 함수 인수-팩 확장 (function parameter pack expansion)

```cpp
template<typename... Ts>
void func(Ts... args)
{
	// sizeof... 는 가변 인수의 개수를 변환한다.
	const int size = sizeof...(args) + 2;

	// 가변 인수를 배열로 만든다.
	int res[size] = { 1, args..., 2 };
	std::cout << "size of " << size << std::endl;

	// 범위 기반 for 문 내부에 가변 인수를 사용할 수 있다.
	for (auto i : { args... }) { std::cout << i << " "; }
	std::cout << std::endl;

	// 람다 내 캡처절 또는 인수로 만들어 사용할 수 있다.
	auto lm = [&, args...] { return print(args...); }
	lm();

}
```

- 템플릿 템플릿 매개변수
    - 템플릿 변환이 되기 전의 또 다른 클래스 템플릿을 매개변수로 사용한다.
    
    ```cpp
    template< 템플릿 매개변수-리스트 > class [식별자] [ = 디폴트 클래스 템플릿 ]
    template< 템플릿 매개변수-리스트 > typename [식별자 ] [ = 디폴트 클래스 템플릿 ]
    ```
    
    ```cpp
    #include <iostream>
    #include <vector>
    #include <deque>
    #include <list>
    
    // 아래는 콘솔에 출력을 위한 << 비트 이동 연산자 오버로딩이다. 참고로 연산자 오버로딩은 암시적인
    // 템플릿 변환만이 가능하다.
    template<template<class, class...> class C, typename T, class... Args>
    std::ostream& operator<<(std::ostream& os, const C<T, Args...>& objs)
    {
    	for (auto const& obj : objs)
    	{
    		os << obj << " ";
    	}
    	return os;
    }
    
    // deque 클래스 template<class T, class Allocator = std::allocator<T>> class deque 로 선언되어 있다.
    // 따라서 V 템플릿 템플릿 매개변수를 대신하여 deque 클래스 템플릿을 암시적인 방법으로 사용하고 자
    // 한다면 2개의 템플릿 매개변수를 선언해주어야 한다.
    template<template<class, class> class V, class T, class A>
    void f(V<T, A>& v)
    {
    	for (auto const& Temp : v)
    	{
    		std::cout << Temp << " ";
    	}
    	std::cout << std::endl;
    }
    
    template<template<class> class v, class T>
    void g(v<T>& v)
    {
    	while (!v.empty())
    	{
    		T temp = v.back();
    		v.pop_back();
    		std::cout << temp << " ";
    	}
    	std::cout << std::endl;
    }
    
    int main()
    {
    	std::vector<double> vf{ 1.1, 2.2, 3.3, 4.4 };
    	// 연산자 오버로딩에 대해 명시적 템플릿 변환을 적용하고 자 한다면 에러가 발생한다.
    	std::cout << vf << std::endl;
    
    	std::deque<int> di{ 1,2,3,4 };
    	f(di);
    	std::list<char> lc{ 'a','b','c','d' };
    	f<std::list, char>(lc);
    
    	//g(di); //암시적 템플릿 변환을 사용하고 자 한다면 에러가 발생한다.
    	g<std::deque, int>(di);
    	return 0;
    }
    ```
    
    ```cpp
    #include <string>
    #include <iostream>
    
    // 타입 템플릿 매개변수를 사용하여 템플릿 클래스를 선언한다.
    template<typename T>
    struct My_Map
    {
    public:
    	My_Map(T t) : Data(t) {}
    	T GetData() { return Data; }
    
    private:
    	T Data;
    };
    
    // 타입 템플릿 매개변수와 템플릿 템플릿 매개변수를 다음과 같이 선언한다.
    template<typename K, typename V, template<typename T> typename C = My_Map>
    class Map
    {
    public:
    	Map(K k, V v) : Key(k), Value(v) {}
    
    	K GetKey() { return Key.GetData(); }
    	V GetValue() { return Value.GetData(); }
    
    private:
    	C<K> Key;
    	C<V> Value;
    };
    
    int main()
    {
    	Map<int, std::string, My_Map> map(1000, "템플릿 템플릿 인수");
    	std::cout << "Map( " << map.GetKey() << ", " << map.GetValue() << " )\n";
    }
    ```
    
    - 위의 프로그램을 보면, 클래스 템플릿의 매개변수로 my_map 클래스 템플릿을 사용하는 것을 전제로 프로그램되어 있다. 따라서 위의 Map 클래스 템플릿은 GetData() 함수를 가지지 않는 다른 클래스 템플릿을 매개변수로 사용할 수 없다.

- 타입이 아닌 템플릿 매개변수(non-type template parameter)
    - 구체적으로 명시한 데이터 타입과 그에 대응되는 인수
    
    ```cpp
    #include <cstring>
    #include <iostream>
    
    // 아래 'int i'처럼 타입이 아닌 템플릿 매개변수는 타입을 나타내는 class나 typename의 지정자를
    // 사용하지 않는다.
    template<int i>
    class A
    {
    public:
    	A() { memset(Array, 0, i * sizeof(int)); }
    	void Print()
    	{
    		//템플릿 인수는 상수처럼 사용할 수 있다.
    		std::cout << "size of " << i << std::endl;
    		for (auto l : Array) { std::cout << l << std::endl; }
    		std::cout << std::endl;
    	}
    
    private:
    	int Array[i]; //배열의 크기를 템플릿 인수로 제공한다.
    	const int Length = i; //배열의 크기를 상수로 사용한다.
    };
    
    int main()
    {
    	//명시적인 방법으로 템플릿 인수의 값을 10으로 할당하였다. 객체 생성과 함께 내부에 10의 크기를
    	//갖는 배열이 생성된다.
    	A<10> a;
    	a.Print();
    }
    ```
    
    - 템플릿 변환 시 마치 템플릿 인수를 상수처럼 사용한다.
    
    ```cpp
    #include <iostream>
    
    // 타입이 아닌 템플릿 매개변수를 참조로 사용한다.
    template<int& ri>
    struct Simple
    {
    	Simple()
    	{
    		printf("객체 생성 시 ri는 %d 이다.\n", ri);
    	}
    	~Simple()
    	{
    		printf("객체 소멸 시 ri는 %d 이다.\n", ri);
    	}
    };
    
    int i = 1;
    
    int main()
    {
    	// 반드시 전역 변수를 사용하여 객체를 생성해야 한다. 만약 지역 변수를 사용한다면, 컴파일 시점에
    	// 데이터를 확정하지 못해 에러가 발생한다.
    	Simple<i> S;
    	i = 0;
    	return 0;
    }
    
    실행결과
    객체 생성 시 ri는 1 이다.
    객체 소멸 시 ri는 0 이다.
    ```
    
    - 템플릿 인수로 리터럴이 아닌 수정 가능한 클래스나 구조체의 인스턴스 그리고 실수는 허용되지 않는다.
    - 결론은 컴파일 타임에 확정된 리터럴을 집어 넣을 수 있다는 것인듯

### 8 - 03 템플릿 특수화

- 템플릿 특수화(Template Specialization) 는 다음과 같이 클래스 템플릿 또는 함수 템플릿을 선언한 이후에 예외의 대상이 되는 특정 데이터 타입을 미리 템플릿 인수로 지정하는 것을 말한다.

```cpp
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

// 클래스 템플릿을 선언하거나 정의한다.
template<typename T>
inline std::string Stringify(T const& x)
{
	std::ostringstream out;
	out << x;
	return out.str();
}

// 아래는 전체 템플릿 특수화로 별도 템플릿 매개변수를 지정하지 않는다. 그리고 템플릿 인수를 지정하여
// 위의 템플릿 매개변수와 또 다른 형식의 함수 오버로딩처럼 사용한다.
template<>
inline std::string Stringify<bool>(bool const& x)
{
	std::ostringstream out;
	out << std::boolalpha << x;
	return out.str();
}

template<>
inline std::string Stringify<double>(double const& x)
{
	std::ostringstream out;
	const int Sigdigits = std::numeric_limits<double>::digits10;
	out << std::setprecision(Sigdigits) << x;
	return out.str();
}

int main()
{
	std::cout << Stringify<int>(100) << ", " << Stringify<bool>(true) << ", " <<
		Stringify<double>(23.65) << std::endl;
}
```

- 전체 템플릿 특수화(Explicit Full Template Specialization)
    - 템플릿에서 선언한 템플릿 매개변수 전체에 대해 특정 데이터 타입으로 템플릿 인수를 지정하는 경우를 말한다.
- 부분 템플릿 특수화(Partial Template Specialization)
    - 템플릿에서 선언한 템플릿 매개변수 가운데 일부에 대해 특정 데이터 타입으로 템플릿 인수를 지정하는 경우를 말한다.

- 전체 템플릿 특수화

```cpp
#include <iostream>

template<class T>
class Form
{
public:
	Form(T* t) : _t(t) {}
	void Print()
	{
		std::cout << *_t << std::endl;
	}

private:
	T* _t;
};

// 아래와 같이 char* 타입을 사용하여 템플릿 변환을 적용한다면, 변환 인수로
// 사용한 데이터 타입에 대해 아래 템플릿이 위의 템플릿보다 우선적으로 적용된다.
template<>
class Form<char*>
{
public:
	Form(char* t) : _t(t) {}
	void Print()
	{
		std::cout << "Form<char*> : " << _t << std::endl;
	}

private:
	char* _t;
};

int main()
{
	int i = 157;
	Form<int> form1(&i); // 기본 템플릿을 적용한다.

	char c[10] = "string1";
	// char* 인수를 사용하여 템플릿 특수화된 클래스 템플릿의 인스턴스를 만든다.
	Form<char*> form2(c);

	form1.Print();
	form2.Print();
}
```

### 8 - 04 타입 특성 클래스 템플릿

- 컴파일러에 타입 정보를 제공해 주는 특수 목적의 클래스 템플릿을 말함

- 아래 함수 템플릿의 경우, 만약 int* 처럼 포인터를 사용한다면, 함수 템플릿은 템플릿 변환후 실행하는 과정에서 예상치 못한 에러가 발생하게 된다.

```cpp
#include <iostream>

template<class T>
T Min(T a, T b)
{
	return (a < b) ? a : b;
}

int main()
{
	int tmp01 = 10;
	int tmp02 = 20;
	int* a = &tmp01, *b = &tmp02;

	std::cout << "1. 최솟값 : " << Min(*a, *b) << std::endl;
	std::cout << "2. 최솟값 : " << Min<int*>(a, b) << std::endl;
}
```

- 대부분 크게 기본 템플릿이나 포인터에 대한 템플릿을 만들어 사용한다.

- enable_if 구조체 템플릿은 bool 타입의 true 또는 false 에 따라 다른 클래스 템플릿 또는 함수 템플릿에 대한 활성화 또는 비활성화시키는 용도로 사용한다.

```cpp
#include <iostream>
#include <type_traits>
#include <string>

using namespace std;

// 템플릿 인수가 lvalue 참조가 아니라면, 아래 함수 템플릿을 활성화시킨다.
template<class T>
typename std::enable_if<!std::is_lvalue_reference<T>::value, T&>::type min(T& a, T& b)
{
	std::cout << "변 수";
	return (a < b) ? a : b;
}

// 템플릿 인수가 lvalue 참고이라면 아래 함수 템플릿을 활성화시킨다.
template<class T>
typename std::enable_if<std::is_lvalue_reference<T>::value, T>::type min(T a, T b)
{
	std::cout << "참 조";
	return (a < b) ? a : b;
}

// 템플릿 인수가 포인터라면 아래 함수 템플릿을 활성화시킨다.
template<class T>
T min(T* a, T* b)
{
	std::cout << "포인터";
	return (*a < *b) ? *a : *b;
}

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

bool operator<(Shape& a, Shape& b)
{
	return a.GetArea() < b.GetArea();
}

bool operator>(Shape& a, Shape& b)
{
	return a.GetArea() > b.GetArea();
}

int main()
{
	int tmp01 = 10;
	int tmp02 = 20;
	int& tmp03 = tmp01;
	int& tmp04 = tmp02;
	int* a = &tmp01, *b = &tmp02;
	std::cout << "1. 최솟값 : " << min<int>(*a, *b) << std::endl;
	std::cout << "2. 최솟값 : " << min<int&>(tmp03, tmp04) << std::endl;
	std::cout << "3. 최솟값 : " << min(a, b) << std::endl;

	Rectangle shape01 = Rectangle("직사각형", 10, 5);
	Circle shape02 = Circle(10);
	std::cout << "4. 최솟값 : ";
	Shape& s1 = min<Shape&>(shape01, shape02);
	s1.GetArea();

	std::cout << "5. 최솟값 : ";
	Shape& s2 = min<Shape>(shape01, shape02);
	s2.GetArea();

	return 0;
}
```

- `std::is_lvalue_reference<T>::value, T&>::type`
    - T 타입이 lvalue 참조냐 아니냐에 따라 활성화 또는 비활성화가 결정됨
    - 이러한 데이터 타입을 `의존 타입`이라 함
- 의존 타입
    - 컴파일하는 과정에서 조건이 맞지 않는다면 컴파일되지 않는 특징이 있음
    - ‘typename’ 지정자를 사용하여 반환되는 함수의 데이터 타입이 의존 타입이란 사실을 명시해 주어야 한다.

### 8 - 05 포워드 참조

```cpp
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
```

### 8 - 08 마무리

- 요점 정리
    - 템플릿은 함수나 클래스를 생성하기 위한 템플릿 메타프로그래밍을 의미하며 실제 함수나 클래스를 의미하지 않는다. 따라서 템플릿에 대한 인스턴스화하는 과정은 다음과 같다.
        - `템플릿 클래스 → 템플릿 변환 → 템플릿 인스턴스화`
    - 템플릿 변환으로 인해 동일한 함수와 클래스가 생성되지 않는다면, 하나 이상의 템플릿을 선언하더라도 아무런 문제가 되지 않는다.
    
    - 기본 템플릿에 적용할 수 없는 타입이 존재한다면, 다음과 같은 방법을 사용할 수 있다.
        - 템플릿 특수화는 예외의 대상이 되는 특정 데이터 타입에 대한 템플릿 변환을 수행한다.
        - 타입 특성 클래스 템플릿 가운데 enable_if 구조체 템플릿을 사용하여 템플릿을 활성화하거나 또는 비활성화시키는 방법을 사용한다.