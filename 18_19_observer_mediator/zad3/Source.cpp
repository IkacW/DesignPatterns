#include<iostream>
#include<limits.h>
#include<vector>

/*
For some functions we will 'add' functions with which we will incrementaly update values of 
miminum, maximum, etc.
*/

class Function {
public:
	virtual void update(int) = 0;
	virtual int f() const = 0; // returns a value of the function
	virtual std::string description() const = 0; // outputs the result
};

class Sum : public Function {
	int s = 0;
public:
	void update(int new_value) override {
		s += new_value;
	}
	std::string description() const override { return "Sum"; }
	int f() const { return s; }
};

class Size : public Function {
	int counter = 0;
public:
	void update(int) override {
		counter++;
	}
	std::string description() const override { return "Size"; }
	int f() const { return counter; }
};

class Min : public Function {
	int min = INT_MAX;
public:
	void update(int new_value) override {
		min = new_value < min ? new_value : min;
	}
	std::string description() const override { return "Min"; }
	int f() const { return min; }
};

class Max : public Function {
	int max = INT_MIN;
public:
	void update(int new_value) override {
		max = new_value > max ? new_value : max;
	}
	std::string description() const override { return "Max"; }
	int f() const { return max; }
};

class Collection {
protected:
	void updateFunctions(int new_value) { for (auto f : functions) f->update(new_value); } // notify
	std::vector<Function*> functions;
public:
	virtual void addElement(int element) = 0;
	std::vector<Function*> getFunctions() const { return functions; }
	void addFunction(Function* f) { functions.push_back(f); }
};

#define MAX_VELICINA 100

class Stack : public Collection {
	int top = 0;
	int arr[MAX_VELICINA];
public:
	void addElement(int element) override {
		arr[top++] = element;
		updateFunctions(element);
	}
};

struct Node {
	Node* next;
	int value;
	Node(int value, Node* next=nullptr): value(value), next(next) {}
};

class SingleLinkedList : public Collection {
	Node* head = nullptr;
public:
	void addElement(int element) override {
		if (!head) { head = new Node(element); }
		else {
			Node* tmp = head;
			head = new Node(element, tmp);
		}
		updateFunctions(element);
	}
};

int main() {
	Collection* k = new Stack();
	k->addFunction(new Size());
	k->addFunction(new Sum());
	k->addFunction(new Min());
	k->addFunction(new Max());

	k->addElement(1);
	k->addElement(11);
	k->addElement(-1);
	k->addElement(100);
	k->addElement(2);
	k->addElement(3);

	auto functions = k->getFunctions();
	for (auto f : functions) {
		std::cout << "Value of " << f->description() << " function is" << f->f() << std::endl;
	}
}