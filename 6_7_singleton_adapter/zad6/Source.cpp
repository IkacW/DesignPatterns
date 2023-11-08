#include<iostream>

/*
6. Create class ShapeDrawerV1 and two methods drawRectangle and drawCircle.
Lets assume that we want to change a bit our software, we want to add new classes which would be used
differently, but because of existing users we want to keep old interface/implementation. 
Create independent abstract class ShapeDrawerV2 which has virtual method
draw(ShapeType). Thereby, old implementation is working and we do not want to implement function from 
scratch, but to use existing one. 
We will solve problem using adapter with which we can enable use of existing class ShapeDrawerV1, 
comunicating throughout new inteface form class ShapeDrawerV2.
*/

class ShapeDrawerV1 {
public:
	void drawRectangle() {
		std::cout << "Drawing rectangle..." << std::endl;
	}
	void drawCircle() {
		std::cout << "Drawing circle..." << std::endl;
	}
};

enum class ShapeType {RECTANGLE, CIRCLE};

class ShapeDrawerV2 {
public:
	virtual void draw(ShapeType) = 0;
	virtual ~ShapeDrawerV2() {}
};

class ShapeDrawerAdapter : public ShapeDrawerV2, private ShapeDrawerV1 {
public:
	void draw(ShapeType type) override {
		std::cout << "ShapeDrawerAdapter: " << std::endl;
		if (type == ShapeType::CIRCLE)
			drawCircle();
		else
			drawRectangle();
	}
};

int main() {
	ShapeDrawerV2* drawer = new ShapeDrawerAdapter();
	drawer->draw(ShapeType::CIRCLE);
	std::cout << std::endl;
	drawer->draw(ShapeType::RECTANGLE);
	return 0;
}