#include <string>
#include <iostream>

// Ÿ�� ���ø� �Ű������� ����Ͽ� ���ø� Ŭ������ �����Ѵ�.
template<typename T>
struct My_Map
{
public:
	My_Map(T t) : Data(t) {}
	T GetData() { return Data; }

private:
	T Data;
};

// Ÿ�� ���ø� �Ű������� ���ø� ���ø� �Ű������� ������ ���� �����Ѵ�.
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
	Map<int, std::string, My_Map> map(1000, "���ø� ���ø� �μ�");
	std::cout << "Map( " << map.GetKey() << ", " << map.GetValue() << " )\n";
}