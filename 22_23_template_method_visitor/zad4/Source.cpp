#include<iostream>

class Visitor;

class Element {
protected:
	int state;
public:
	Element(int state): state(state) {}
	int getState() const { return state; }
	virtual void baseFunctionality() = 0;
	// this method is here just to simulate that this class is 'doing something' in real use, and
	// visitors are here to add more functionalities to this class without touching it
	
	// It's named like this just to be more clear what the purpose is of visitor, but it's often named accept.
	virtual void executeNewFunctionality(Visitor*) = 0;
	virtual ~Element() {}
};

class ConcreteElementA : public Element {
public:
	using Element::Element;
	void baseFunctionality() override { std::cout << "Base functionality A" << std::endl; }
	void executeNewFunctionality(Visitor*) override; // Will be implemented later in a code
	// because of class implementation order .
};

class ConcreteElementB : public Element {
public:
	using Element::Element;
	void baseFunctionality() override { std::cout << "Base functionality B" << std::endl; }
	void executeNewFunctionality(Visitor*) override; 

class Visitor {
public:
	// This is important: visitor must know how to 'visit' every concrete class . 
	virtual void visit(ConcreteElementA*) = 0;
	virtual void visit(ConcreteElementB*) = 0;
	virtual ~Visitor() {}
};

class NewOperation1 : public Visitor {
public:
	void visit(ConcreteElementA* a) override {
		std::cout << "Executing new operation 1 on ConcreteElementA with state" << a->getState() << std::endl;
	}
	void visit(ConcreteElementB* a) override {
		std::cout << "Executing new operation 1 on ConcreteElementB with state " << a->getState() << std::endl;
	}
};

class NewOperation2 : public Visitor {
public:
	void visit(ConcreteElementA* a) override {
		std::cout << "Executing new operation 2 on ConcreteElementA with state " << a->getState() << std::endl;
	}
	void visit(ConcreteElementB* a) override {
		std::cout << "Executing new operation 2 on ConcreteElementB with state " << a->getState() << std::endl;
	}
};

void ConcreteElementA::executeNewFunctionality(Visitor* p) {
	p->visit(this);
}

void ConcreteElementB::executeNewFunctionality(Visitor* p) {
	p->visit(this);
}

int main() {
	Element* e1 = new ConcreteElementA(123);
	Element* e2 = new ConcreteElementB(321);
	Visitor* p1 = new NewOperation1();
	Visitor* p2 = new NewOperation2();
	e1->executeNewFunctionality(p1);
	e1->executeNewFunctionality(p2);
	e2->executeNewFunctionality(p1);
	e2->executeNewFunctionality(p2);

	delete e1;
	delete e2;
	delete p1;
	delete p2;

	return 0;
}