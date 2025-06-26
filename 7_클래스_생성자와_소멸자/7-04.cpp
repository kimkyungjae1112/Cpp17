#include <iostream>

class Box
{
public:
	Box(int width = 0, int length = 0, int height = 0) : 
		width(width), length(length), height(height) {}

	inline int GetVolume() { return width * length * height; }

private:
	int width;
	int length;
	int height;
};

class WoodBox : public Box
{
public:
	// "uinsg Box::Box;" 선언문은 아래 라인과 동일한 기능을 수행
	// WoodBox(int w, int l, int h) : Box(w, l, h) {}
	using Box::Box;
};

int main()
{
	WoodBox* WB = new WoodBox(5, 10, 3);
	WB->GetVolume();
	delete WB;
}