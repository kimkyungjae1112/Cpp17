//��ü ���� �������� ����
#include <iostream>
#include <string>
using namespace std;

struct Person
{
	// �Ʒ��� Person ����ü�� �������̴�.
	Person(string n) { name = n; }
	
	// person ����ü�� string Ÿ���� �̸��̶� ������ ����Ѵ�.
	string name;
};

// �Ʒ� Student ����ü�� Person ����ü�� ��ӹ޴´�.
struct Student : public Person
{
	// �Ʒ� �����ڴ� Person ��ü�� �����ϰ� u�� id�� �й��� �ο��Ѵ�.
	Student(string i, int n) : Person(i) { id = n; }
	int id;
};

int main()
{
	// 1. Student Ÿ���� ������ �����Ѵ�.
	Student d("�̼���", 2013);

	// 2. ��ü ���� ����� �������� ��Ģ�� ���� ��-ĳ������ ����Ͽ� Student Ŭ���� Ÿ����
	//    ��ü�� ���� Person Ŭ���� Ÿ�̺��� ������ ��ȯ�Ѵ�.
	Person& b = d; // "dynamic_cast<Person&>(d);" ���� ��ó�� �����ϴ�.

	// 3. �ٽ� ���� Ŭ������ ������ ��ȯ(casting) �Ѵ�.
	Student& d1 = (Student&)b;
	cout << d.name << ", " << b.name << ", " << d1.name << endl;

	// �Ʒ��� ���� �ּҸ� ����ϸ�, ��� ���� �ּҸ� ����Ų��.
	cout << &d << ", " << &b << ", " << &d1 << endl;

	Student dd("����", 2039);
	// 4. ���� Ŭ���� Ÿ���� ������ ���� ����ȴ�.
	Person bb = (Person)dd;
	cout << bb.name << endl;

	// dd ������ bb ������ ���� �ٸ� �ּҸ� ����Ų��. ������ ���簡 �̷������.
	cout << &dd << ", " << &bb << endl;

	// 5. ����! Person ��ü�κ��� Student ��ü�� �ٿ�-ĳ��Ʈ�� �� ����.
	// Student dd2 = (Student) bb;

	return 0;
}