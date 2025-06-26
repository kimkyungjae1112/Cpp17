#pragma once
#ifndef  Door_hpp
#define Door_hpp

extern int MyGlobal; // 외부에 선언된 전역 변수를 사용할 때 extern 키워드를 사용한다.

// 선언문을 포함하는 네임스페이스를 지정한다.
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