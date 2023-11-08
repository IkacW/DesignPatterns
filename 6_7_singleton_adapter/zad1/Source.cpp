#include<iostream>

// Podsetnik: ideja ovog pristupa kao i svih narednih je da je životni vek statičkih atributa cela aplikacija. 
class BaseSingleton {
public:
	// it's important to be a static function, so we can call it without instancig object
	static BaseSingleton* getInstance() { 
		if (!instance) // idea is that static variable is initialised only at first call of a contstructor
			instance = new BaseSingleton();
		return instance; 
	}
	void use() {
		std::cout << "Using Singleton object" << std::endl;
	}
private:
	// In this way we ensure that we can not call constructor outside of a class, which means that we 
	// can not make multiple objects of this type
	BaseSingleton() { std::cout << "Creating Singleton object" << std::endl; };
	BaseSingleton(const BaseSingleton&) = default;
	BaseSingleton& operator=(const BaseSingleton&) = default;

	static BaseSingleton* instance;
};

BaseSingleton* BaseSingleton::instance = nullptr;

int main() {
	BaseSingleton* singleton = BaseSingleton::getInstance();
	singleton->use();
	BaseSingleton::getInstance()->use();
	return 0;
}