#include<iostream>
#include<string>

class Memento {
	std::string state;
public:
	Memento(const std::string& state): state(state) {}
	std::string getState() const { return state; }
	void setState(const std::string& state) { this->state = state; } //seter ne mora da postoji
};

class Originator {
	std::string state;
public:
	Originator(const std::string& state): state(state) {}
	void setMemento(const Memento* m) { 
		std::cout << "Vracam objekat na ranije sacuvano stanje\n";
		this->state = m->getState();
	}
	Memento* createMemento() const { return new Memento(state); }
	void modifyState() { 
		std::cout << "Modifikujem stanje objekta\n";
		state += std::to_string(rand() % 10); 
	}
	
	std::string describe() const { return state; }
};

class Caretaker {
	const Memento* m; // It's important to prohibit modification of memento.
	// That could be accomplishe with not implementing setters to memento class.
	// That could be accomplished by not implementing setters in the memento class.
public:
	void setMemento(const Memento* m) { 
		std::cout << "Cuvam novi podsetnik\n";
		this->m = m; 
	}
	const Memento* getMemento() const { return m; }
	~Caretaker() { delete m; }
};

int main() {
	Originator o("...");
	Caretaker caretaker;
	std::cout << "o.describe(): " << o.describe() << std::endl;
	o.modifyState();
	caretaker.setMemento(o.createMemento());
	std::cout << "o.describe(): " << o.describe() << std::endl;
	o.modifyState();
	std::cout << "o.describe(): " << o.describe() << std::endl;
	o.modifyState();
	std::cout << "o.describe(): " << o.describe() << std::endl;
	o.setMemento(caretaker.getMemento());
	std::cout << "o.describe(): " << o.describe() << std::endl;
	return 0;
}