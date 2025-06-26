# 편리하고 유용한 클래스-1 10

- 문자열 클래스
- 시간과 타이머
- pair 구조체와 tuple 클래스
- 스트림 클래스
- 파일 입출력 스트림 클래스
- 디렉토리 및 파일 관리
- 문자열 스트림(String Stream)
- 마무리

---

- STL로 제공하는 클래스 가운데 알면 편리하고 유용한 클래스에 대해 알아봄
- C언어의 입출력
    - 파일 입출력
        - 하위 레벨 입출력 ( low-level I/O )
        - 파일 입출력은 운영체제에서 사용하는 파일 식별자 ( file descriptor, FD )와 함께 함수의 일종인 시스템콜을 호출함으로써 저장 장치 내 파일의 입출력 작업을 수행한다.
    - 표준 입출력
        - 상위 레벨 입출력 ( high-level I/O )
        - 버퍼를 통해 데이터의 입출력을 수행한다.
        - 표준 입출력이 제공하는 함수는 시스템콜을 호출하여 개발자를 대신하여 필요한 작업을 수행한다.
- C++ 의 입출력
    - C언어에서 제공하는 기능 모두 사용 가능
    - 스트림 방식으로 제작된 클래스를 별도 라이브러리로 제공

- 이번 장에서는 라이브러리로 제공되는 입출력 스트림과 저장 매체에 기록하는 파일 스트림 그리고 문자열을 처리하는 문자열 스트림에 대해 알아보도록 한다.

### 10 - 1 문자열 클래스

string 클래스는 basic_string 클래스 템플릿으로 다음과 같이 선언된 클래스이다.

```cpp
_EXPORT_STD template <class _Elem, class _Traits = char_traits<_Elem>>
using basic_string = _STD basic_string<_Elem, _Traits, polymorphic_allocator<_Elem>>;

_EXPORT_STD using string = basic_string<char>;
```

string 클래스는 다음과 같은 기본적인 함수를 제공한다.

```cpp
string MyString;
cout << "MyString 변수의 기본 할당 크기 " << MyString.capacity() << endl;
cout << "MyString 변수의 최대 입력 크기 " << MyString.max_size() << endl;

MyString = "Hello World!";
cout << "MyString 변수의 할당 크기 " << MyString.capacity() << endl;
cout << "MyString 변수의 크기 " << MyString.length() << endl; //size() 함수와 동일

//실행 결과
MyString 변수의 기본 할당 크기 15
MyString 변수의 최대 입력 크기 9223372036854775807
MyString 변수의 할당 크기 15
MyString 변수의 크기 12
```

string 객체가 선언되면 기본적으로 4비트 - 1 크기를 확보한 후 해당 크기를 넘어가면 비트 수를 두 배씩 늘려서 메모리를 할당받는다. 가변 길이 배열인 벡터와 유사

- max_size() : 문자열로 처리할 수 있는 가장 큰 크기
- length(), size() : 모두 현재 객체에 담겨져 있는 문자열의 크기(정확하게 문자 개수)

string 클래스는 다음과 같은 장점을 제공한다.

1. 복함 함수의 기능을 제공한다.
    
    문자열 사이의 작업을 수행할 때 별도 변수를 새롭게 생성하거나 malloc() 함수를 사용하여 재생성할 필요 없이 다음과 같이 문장으로 처리 할 수 있다.
    
    ```cpp
    // C++ 스타일 문자열
    string a = "Hello World!";
    string b = "안녕하세요";
    string c = a + " " + b;
    cout << c << endl;
    ```
    
    반면 C언어의 문자열은…
    
    ```cpp
    // C 스타일 문자열
    const char* d = "Hello World!";
    const char* e = "안녕하세요";
    
    size_t length = strlen(d) + strlen(e) + 2;
    char* f = (char*)malloc(length);
    
    snprintf(f, length, "%s %s", d, e);
    cout << f << endl;
    free(f);
    ```
    

1. 문자열의 비교
    
    문자열의 알파벳과 한글의 가나다 순에 따라 다음과 같이 string 클래스에서 제공하는 함수를 사용하여 상호 문자열을 비교할 수 있다.
    
    ```cpp
    f (a.compare(b) == 0)
    		cout << a << " == " << b << endl;
    	// 문자열의 차이가 없다면 두 개의 문자열이 같다는 것을 의미
    	else if (a.compare(b) < 0)
    		cout << a << " > " << b << endl;
    	// a이 b보다 사전 순으로 앞서 있음을 의미한다.
    	else if (a.compare(b) > 0)
    		cout << a << " < " << b << endl;
    	// a이 b보다 사전 순으로 뒤에 있음을 의미한다.
    ```
    

  

1. 문자열의 교체
    
    ```cpp
    string g = "Hello World! 안녕하세요";
    const string search = "World!";
    
    // find() 함수는 인수로 제공된 문자열이 객체 내 존재한다면 해당 위치를 숫자로 반환한다.
    // size_type 타입은 원래 문자열의 크기를 나타내는 타입이다. 사실 size_t 임 그냥
    std::string::size_type s = g.find(search);
    
    // npos 상수는 클래스에서 "static const size_type npos = -1;" 로 선언되어 있다.
    // 만약 find() 함수가 npos 상수를 반환한다면 문자열을 찾을 수 없다는 의미이다.
    if (string::npos != s)
    {
    	// 6번 인덱스
    	cout << g << '"' << search << "\"의 위치는 " << s << endl;
    }
    
    size_t pos = 0;
    string replace = "a";
    
    // 변경하고 자 하는 문자열이 하나 이상일 수 있으므로 다음과 같이 while 문을 사용하였다.
    while (string::npos != (pos = g.find(search, pos)))
    {
    	g.replace(pos, search.length(), replace);
    
    	// g 문자열은 교체되었기 때문에 교체한 문자열의 크기만큼 다시 이동한다.
    	// 이동하지 않는다면 같은 위치에서 다시 문자열을 찾게 된다.
    	pos += replace.length();
    }
    
    cout << g << endl;
    ```
    

유용한 함수 모음

- size_type find( const basic_string& str, size_type pos = 0 ) const;
    - 첫 번째 인수와 같은 문자열이 존재한다면, 문자열이 존재하는 위치를 반환, 찾을 수 없다면 -1
    - 두 번째 인수는 검색을 처음 시작하는 위치
- basic_string& replace( size_type pos, size_type count, const basic_string& str )
    - 첫 번째 인수는 교체하는 문자열의 시작 위치
    - 두 번째 인수는 교체하고 자 하는 문자열의 수
    - 세 번째 인수는 교체 문자열
    - 반환되는 데이터는 교체된 이후의 문자열
- char& at ( size_type pos )
    - pos 인수가 가리키는 위치의 문자를 참조로 만들어 변환
- const char* c_str() const
- const char* data() const
    - 위 두 함수는 string 객체 내 const char*을 가리킨다.
    - 따라서 객체가 삭제될 때 자동 삭제

- bool empty() const
    - 문자열 객체가 비어있다면 true
- string substr( size_t pos = 0, size_t = npos ) const
    - 문자열 내 내부 문자열을 복사하여 새로운 문자열 객체를 만들어 반환한다.
- string to_string (primitive val)
- primitive sto i ~ ld ( const string& str, size_t* pos = 0 )

### 10 - 2 시간과 타이머

C++ 11 이전에는 C언어에서 제공하는 time() 함수와 time_t라는 데이터 타입을 사용해 시간을 표현했지만, C++ 11 이후에는 chrono 라고 하는 라이브러리가 나와 주로 사용한다.

chrono 클래스는 다음과 같은 클래스를 제공한다.

- system_clock 클래스는 시스템에 요청하여 날짜와 시간을 반환받을 때 사용하는 클래스
- steady_clock 클래스는 초시계처럼 시간 간격을 측정할 때 사용하는 클래스
- high_resolution_clock 클래스는 비교적 짧은 시간을 측정할 때 사용하는 클래스

```cpp
#include <iostream>
#include <chrono>
#include <ctime>
#include <format>
#include <iomanip>
using namespace std;

int main()
{
	// system_clock::now() 함수를 통해 현재 시간을 얻는다.
	chrono::system_clock::time_point now = chrono::system_clock::now();

	// time_point 클래스 템플릿은 현재 시점의 시간을 제공한다.
	// 따라서 우리가 알 수 있는 시간을 보기 위해서 다음과 같이 system_clock 클래스에서 제공하는
	// to_time_t() 함수를 사용하여 time_t 타입의 시간(에포크 시간)으로 바꾸어 출력해야 한다.
	time_t epoch = chrono::system_clock::to_time_t(now);
	cout << "1970년 1월 1일 00:00:00 이후 진행된 시간(초) : " << epoch << endl;

	// time_point로부터 직접 에포크 시간을 알기 위해 chrono::duration_cast() 함수를
	// 사용하여 다음과 같이 변환을 거쳐야 한다.
	cout << chrono::duration_cast<chrono::seconds>(now.time_since_epoch()).count() << endl;
	
	// 해당 방식은 시간이 흐르면서 unsafe한 방법이 되었나보다.
	//// localtime() 함수를 사용하여 지역 시간으로 바꾸어 출력한다.
	//cout << "현재 시간 : " << put_time(localtime(&epoch), "%c") << endl;

	//// 현재 시간에서 24 시간을 빼서 어제 시간을 환산한다.
	//time_t now_c = chrono::system_clock::to_time_t(now - chrono::hours(24));
	//cout << "어제 시간 : " << put_time(localtime(&now_c), "%F %T") << '\n';

	// C++ 20 방식
	auto now20 = chrono::system_clock::now();
	auto zt = chrono::zoned_time{ chrono::current_zone(), now };  // 지역 시간대 고려
	cout << format("{:%F %T}", zt) << endl;
}

```

### 10 - 3 pair 구조체와 tuple 클래스

std::pair 구조체

```cpp
#include <utility>		// std::pair, std::make_pair
#include <string>		// std::string
#include <algorithm>	// std::sort
#include <tuple>		// std::tuple
#include <iostream>		// std::cout
#include <vector>		// std::vector

// 자주 사용하는 pair 구조체는 아래와 같이 typedef를 사용하여 미리 선언하는 것이 좋다.
typedef std::pair <std::string, double> MyPair;

// 아래 Compare() 함수는 데이터를 정렬할 때 사용하는 함수로 첫 번째 인수가 두 번째 인수보다 적을 때
// 또는 순서가 빠를 때 반환하는 값을 true로 한다면, 이는 오름차순(1,2,3,4)으로 정렬을 의미한다.
// 만약 false 한다면 내림차순(4,3,2,1)으로 정렬된다.
bool Compare(const MyPair& i, const MyPair& j)
{
	return i.second < j.second;
}

int main()
{
	MyPair Product1;					// 디폴트 생성자이다.
	MyPair Product2("Tomatoes", 2.3);	// 초기화한다.
	MyPair Product3(Product2);			// 복사 생성자로 pair 객체를 생성한다.
	MyPair Product4;

	// make_pair는 임시 pair 객체를 만드는 동시에 std::move의 기능을 제공한다.
	Product1 = std::make_pair(std::string("lightbulbs"), 5.99);

	// first 변수는 pair 클래스 템플릿의 첫 번째 인수에 대응되는 변수를 말한다.
	// 첫 번째 인수는 std::string으로 선언되어 있어 입력에 문제가 없다.
	Product4.first = "shoes";

	// second 변수는 pair 클래스 템플릿의 두 번째 인수에 대응되는 변수이다.
	Product4.second = 39.90;

	std::vector<MyPair> Product(5);
	Product[0] = Product1;
	Product[1] = Product2;
	Product[2] = Product3;
	Product[3] = Product4;
	Product[4] = std::make_pair<std::string, double>("apple", 3.10);

	// 값을 기준으로 정렬한다. 객체의 순서는 앞에서 소개한 Compare() 함수가 제공한다.
	std::sort(Product.begin(), Product.end(), Compare);

	for (int i = 0; i < Product.size(); ++i)
	{
		std::cout << i << ". " << Product[i].first << "의 가격은 $ " << Product[i].second << "이다." << std::endl;
	}
	return 0;
}

// 실행 결과
0. Tomatoes의 가격은 $ 2.3이다.
1. Tomatoes의 가격은 $ 2.3이다.
2. apple의 가격은 $ 3.1이다.
3. lightbulbs의 가격은 $ 5.99이다.
4. shoes의 가격은 $ 39.9이다.
```

vector나 array와 같은 컨테이너 클래스와 함께 pair 구조체를 사용한다면, 구조체의 생성자를 사용하여 객체를 생성하는 것보다 make_pair() 함수를 사용하는 것이 좋은 성능을 제공한다.

std::tuple 클래스

```cpp
#include <tuple>
#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 아래는 Account 타입으로 tuple 클래스 템플릿은 가변 템플릿 매개 변수를 사용한다.
// tuple 의 멤버 변수의 순서는 템플릿 매개변수의 순서와 같다.
typedef std::tuple<string, string, int> Account;

// std::tie 는 tuple 의 각 위치별로 대응되는 값을 개별 변수로 가져올 때 사용한다.
// tie() 함수를 사용하지 않는다면 get() 함수를 사용하여 멤버를 반환받아야 한다.
void print(Account& Val)
{
	string account;
	string name;
	int bal;

	// tie 함수 내 참조 타입의 인수로 읽어들인다. 만약 인수와 서로 다른 타입이라면 에러가 발생한다.
	tie(account, name, bal) = Val;

	printf("계좌 : %s, 소유자 : %s", account.data(), name.data());
	printf(",\t 잔액 : %d\n", bal);
}

// 아래 함수는 데이터를 정렬할 때 사용한다. get() 함수를 사용한다면
// 아래와 같이 tuple 내 요소의 위치를 템플릿 인수로 지정해 주어야 한다.
bool Compare(const Account& i, const Account& j)
{
	return get<2>(i) < get<2>(j);
}

int main()
{
	vector<Account> array = {
		make_tuple("120-333", "홍길동", 6000),
		make_tuple("123-456", "이순신", 2000),
		make_tuple("1532-235", "김구", 7000)
	};

	Account lee("23-35-546", "이성계", 333);
	Account kim("3", "김유신", 100);

	string name;
	int bal;

	// std::ignore 는 tie() 함수 내 해당 위치의 인수값을 무시할 때 사용한다.
	tie(std::ignore, name, bal) = lee;
	cout << name << ", " << bal << endl;

	// std::tuple_cat() 함수는 서로 다른 두 개의 tuple을 한 개로 연결하여 새로운 tuple 객체를
	// 생성할 때 사용한다. 이 경우 별도 타입이 없으므로 auto 타입으로 만든다.
	auto myNums = tuple_cat(lee, kim);
	// string string int string string int

	// 벡터에 각각의 요소를 입력한다.
	array.push_back(lee);
	array.push_back(kim);

	// tuple 클래스 템플릿의 객체는 무명 변수를 생성하여 전달할 수 있는 
	// std::forward_as_tuple() 함수 또는 make_tuple() 함수를 많이 사용한다.
	array.push_back(std::forward_as_tuple("123-15-35", "권율", 2000));

	std::sort(array.begin(), array.end(), Compare);
	for (auto& a : array)
	{
		print(a);
	}
	return 0;
}

```

### 10 - 4 스트림 클래스

최상위 ios_base 클래스 템플릿은 입출력과 관련된 기본적인 함수를 하위 클래스 템플릿에 제공한다.