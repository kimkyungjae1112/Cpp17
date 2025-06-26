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