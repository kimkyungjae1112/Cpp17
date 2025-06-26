//객체 지향 다형성의 원리
#include <iostream>
#include <string>
using namespace std;

struct Person
{
	// 아래는 Person 구조체의 생성자이다.
	Person(string n) { name = n; }
	
	// person 구조체는 string 타입의 이름이란 변수를 사용한다.
	string name;
};

// 아래 Student 구조체는 Person 구조체를 상속받는다.
struct Student : public Person
{
	// 아래 생성자는 Person 객체를 생성하고 u도 id에 학번을 부여한다.
	Student(string i, int n) : Person(i) { id = n; }
	int id;
};

int main()
{
	// 1. Student 타입의 변수를 생성한다.
	Student d("이순신", 2013);

	// 2. 객체 지향 언어의 다형성의 원칙에 따라 업-캐스팅을 사용하여 Student 클래스 타입의
	//    객체를 상위 Person 클래스 타이브이 참조로 변환한다.
	Person& b = d; // "dynamic_cast<Person&>(d);" 으로 대처가 가능하다.

	// 3. 다시 하위 클래스의 참조로 변환(casting) 한다.
	Student& d1 = (Student&)b;
	cout << d.name << ", " << b.name << ", " << d1.name << endl;

	// 아래와 같이 주소를 출력하면, 모두 같은 주소를 가리킨다.
	cout << &d << ", " << &b << ", " << &d1 << endl;

	Student dd("원균", 2039);
	// 4. 상위 클래스 타입의 변수로 복사 저장된다.
	Person bb = (Person)dd;
	cout << bb.name << endl;

	// dd 변수와 bb 변수는 서로 다른 주소를 가리킨다. 변수의 복사가 이루어진다.
	cout << &dd << ", " << &bb << endl;

	// 5. 에러! Person 객체로부터 Student 객체로 다운-캐스트할 수 없다.
	// Student dd2 = (Student) bb;

	return 0;
}