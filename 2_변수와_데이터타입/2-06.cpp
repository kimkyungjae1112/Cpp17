#pragma warning(disable : 4996) //윈도우라면 이 문장을 추가시켜 준다.
#include <iostream>
#include <cstring>

// 데이터 타입별 상수를 선언한다.
#define None 1
#define Integer 2
#define Float 3
#define String 4

// 같은 메모리 영역을 정수와 실수 그리고 문자열로 공유한다.
union DataValue
{
	int Vint;
	float Vfloat;
	char* Vstring;
};

struct DataNode
{
	//콘솔 화면에서 받는 문자의 데이터 타입을 넣는 변수이다.
	int Type;
	DataValue Value;

	// ReadSomeInput() 함수는 콘솔로 입력되는 문자를 받아 정수 또는 실수 그리고 문자열에 따라 아래 Type변수와 Value 변수에 데이터를 입력시켜 주는 기능을 하는 함수이다.
	void ReadSomeInput()
	{
		char* p;

		//입력 문자를 받는데 있어 최대 크기를 100으로 잡았다. 더 좋은 방법은
		//"std::string s;" 처럼 char 타입이 아닌 std::string 타입으로 잡는게 좋다.
		char s[100];
		std::cout << "문자나 정수 그리고 실수 입력을 부탁합니다.";
		std::cin >> s;

		//입력된 문자가 정수인지 확인한다.
		long l = strtol(s, &p, 10);
		if (*p == 0) //반환하는 char 타입의 위치가 NULL이면 입력된 문자가 정수임을 나타낸다.
		{
			Type = Integer;
			Value.Vint = 1;
			return;
		}

		//입력된 문자가 실수인지 확인한다.
		float f = strtof(s, &p);
		if (*p == 0)
		{
			Type = Float;
			Value.Vfloat = f;
			return;
		}

		//이도저도 아니라면 문자열로 처리한다.
		Type = String;

		//\0를 추가하기 위해 한바이트를 늘린다.
		rsize_t len = strlen(s) + 1;
		Value.Vstring = (char*)malloc(len);
		strcpy(Value.Vstring, s);
	}

	//문자열은 malloc() 함수를 호출하여 힙 메모리를 할당받았기 때문에 필요하다면
	//다음과 같이 삭제시켜 주어야 한다.
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
	DataNode InputData; // DataNode 공유체 타입의 변수를 선언한다.
	InputData.ReadSomeInput();

	//타입에 따라 선택하여 데이터를 출력한다.
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

	//작업 완료후에 만약 문자열을 할당받았다면 다음과 같이 해제시켜주어야 한다.
	InputData.FreeString();
}