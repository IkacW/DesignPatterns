#include<iostream>
#include<vector>
/*
7.	Adapter can be used in modified form for using two completely independent classes with same inteface.
Create abstarct class Target vith virtual method print(std::string) and three
independent classes A, B i C with methods printA(std::string), printB(std::string), 
printC(std::string) (every method in separate class). Create template class PrintAdapter,  
that receives a parameter class that has to be adapted. 
Implement PrintAdapter like an object adapter and pass a pointer to a method which has to be executed 
as an argument during the creation of an object. 
*/

class Target {
public:
	virtual void print(const std::string&) = 0;
	virtual ~Target(){}
};

class A {
public:
	void printA(const std::string& message) {
		std::cout << "ClassA: " << message << std::endl;
	}
};


class B {
public:
	void printB(const std::string& message) {
		std::cout << "ClassB: " << message << std::endl;
	}
};


class C {
public:
	void printC(const std::string& message) {
		std::cout << "ClassC: " << message << std::endl;
	}
};

template<class Adaptee>
class PrintAdapter : public Target {
private:
	void (Adaptee::* method)(const std::string&);
	Adaptee* adaptee;
public:
	PrintAdapter(Adaptee* adaptee, void (Adaptee::* method)(const std::string&)):
		method(method), adaptee(adaptee) {}
	void print(const std::string& message) override {
		(adaptee->*method)(message);
	}
	~PrintAdapter() {
		delete adaptee;
	}
};

int main() {
	std::vector<Target*> printers; 
	printers.push_back(new PrintAdapter<A>(new A(), &A::printA));
	printers.push_back(new PrintAdapter<B>(new B(), &B::printB));
	printers.push_back(new PrintAdapter<C>(new C(), &C::printC));

	for (int i = 0; i < printers.size(); ++i) {
		printers[i]->print("message...");
		std::cout << std::endl;
	}
	return 0;
}