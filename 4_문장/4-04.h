#pragma once
#ifndef  Door_hpp
#define Door_hpp

extern int MyGlobal; // �ܺο� ����� ���� ������ ����� �� extern Ű���带 ����Ѵ�.

// ������ �����ϴ� ���ӽ����̽��� �����Ѵ�.
namespace MyNamespace
{
	struct Door
	{
		void Open();
		void Close();
		void ShowState() const;

		void SetName(std::string Str);
		std::string GetName() const;

		void State(int I);

		int IState;
		std::string Name;
	};

	inline void Door::State(int I)
	{
		IState = I;
	}
}

#endif // ! Door_hpp