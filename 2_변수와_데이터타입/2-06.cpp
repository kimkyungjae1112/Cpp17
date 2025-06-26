#pragma warning(disable : 4996) //�������� �� ������ �߰����� �ش�.
#include <iostream>
#include <cstring>

// ������ Ÿ�Ժ� ����� �����Ѵ�.
#define None 1
#define Integer 2
#define Float 3
#define String 4

// ���� �޸� ������ ������ �Ǽ� �׸��� ���ڿ��� �����Ѵ�.
union DataValue
{
	int Vint;
	float Vfloat;
	char* Vstring;
};

struct DataNode
{
	//�ܼ� ȭ�鿡�� �޴� ������ ������ Ÿ���� �ִ� �����̴�.
	int Type;
	DataValue Value;

	// ReadSomeInput() �Լ��� �ַܼ� �ԷµǴ� ���ڸ� �޾� ���� �Ǵ� �Ǽ� �׸��� ���ڿ��� ���� �Ʒ� Type������ Value ������ �����͸� �Է½��� �ִ� ����� �ϴ� �Լ��̴�.
	void ReadSomeInput()
	{
		char* p;

		//�Է� ���ڸ� �޴µ� �־� �ִ� ũ�⸦ 100���� ��Ҵ�. �� ���� �����
		//"std::string s;" ó�� char Ÿ���� �ƴ� std::string Ÿ������ ��°� ����.
		char s[100];
		std::cout << "���ڳ� ���� �׸��� �Ǽ� �Է��� ��Ź�մϴ�.";
		std::cin >> s;

		//�Էµ� ���ڰ� �������� Ȯ���Ѵ�.
		long l = strtol(s, &p, 10);
		if (*p == 0) //��ȯ�ϴ� char Ÿ���� ��ġ�� NULL�̸� �Էµ� ���ڰ� �������� ��Ÿ����.
		{
			Type = Integer;
			Value.Vint = 1;
			return;
		}

		//�Էµ� ���ڰ� �Ǽ����� Ȯ���Ѵ�.
		float f = strtof(s, &p);
		if (*p == 0)
		{
			Type = Float;
			Value.Vfloat = f;
			return;
		}

		//�̵����� �ƴ϶�� ���ڿ��� ó���Ѵ�.
		Type = String;

		//\0�� �߰��ϱ� ���� �ѹ���Ʈ�� �ø���.
		rsize_t len = strlen(s) + 1;
		Value.Vstring = (char*)malloc(len);
		strcpy(Value.Vstring, s);
	}

	//���ڿ��� malloc() �Լ��� ȣ���Ͽ� �� �޸𸮸� �Ҵ�޾ұ� ������ �ʿ��ϴٸ�
	//������ ���� �������� �־�� �Ѵ�.
	void FreeString()
	{
		if (String == Type)
		{
			free(Value.Vstring);
		}
	}
};

int main()
{
	DataNode InputData; // DataNode ����ü Ÿ���� ������ �����Ѵ�.
	InputData.ReadSomeInput();

	//Ÿ�Կ� ���� �����Ͽ� �����͸� ����Ѵ�.
	switch (InputData.Type)
	{
	case Integer:
		std::cout << "Integer : " << InputData.Value.Vint << std::endl;
		break;
	case Float:
		std::cout << "Float : " << InputData.Value.Vfloat << std::endl;
		break;
	case String:
		std::cout << "String : " << InputData.Value.Vstring << std::endl;
		break;
	}

	//�۾� �Ϸ��Ŀ� ���� ���ڿ��� �Ҵ�޾Ҵٸ� ������ ���� ���������־�� �Ѵ�.
	InputData.FreeString();
}