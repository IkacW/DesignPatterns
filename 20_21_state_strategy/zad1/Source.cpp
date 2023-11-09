#include<iostream>

class Person;

class Mood { // stanje
public:
	virtual void work(Person*) = 0;
	virtual void haveFun(Person*) = 0;
	virtual ~Mood() {}
};

class Person {
	std::string name;
	std::string last_name;
	Mood* mood;
public:
	Person(const std::string& name, const std::string& last_name);
	std::string getName() const { return name; }
	std::string getLastName() const { return last_name; }
	void setMood(Mood* mood) {
		this->mood = mood;
	}
	void work() { mood->work(this); }
	void haveFun() { mood->haveFun(this); }
	~Person() { delete mood; }
};

class GoodMood : public Mood {
	void work(Person* o) override; 
	//in implementation we will use class BadMood which is later used, so this definition is moved
	void haveFun(Person* o) override;
};

class BadMood : public Mood {
	void work(Person* o) override {
		std::cout << "Person " << o->getName() << " "
			<< o->getLastName() << " works and is in bad mood!\n";
		if (rand() % 4 == 0) {
			o->setMood(new GoodMood());
			delete this; 
		}
	}
	void haveFun(Person* o) override {
		std::cout << "Person " << o->getName() << " "
			<< o->getLastName() << " is having fun and is in a bad mood!\n";
		if (rand() % 10 < 7) {
			o->setMood(new GoodMood());
			delete this;
		}
	}
};

void GoodMood::work(Person* o) {
	std::cout << "Person " << o->getName() << " "
		<< o->getLastName() << " works and is in good mood!\n";
	if (rand() % 2 == 0) {
		o->setMood(new BadMood());
		delete this;
	}
}
void GoodMood::haveFun(Person* o) {
	std::cout << "Person " << o->getName() << " "
		<< o->getLastName() << " is having fun and is in a good mood!\n";
	if (rand() % 10 == 0) {
		o->setMood(new BadMood());
		delete this;
	}
}

Person::Person(const std::string& name, const std::string& last_name) :
	name(name), last_name(last_name),
	mood(new GoodMood()) {}


int main() {
	srand(time(0));
	Person* o = new Person("Pera", "Peric");
	for (int i = 0; i < 20; i++) {
		o->work();
		o->haveFun();
	}
	delete o;
	return 0;
}