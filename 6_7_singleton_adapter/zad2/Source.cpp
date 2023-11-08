#include<iostream>

class BaseSingleton {
public:
	static BaseSingleton& getInstance() {
		static BaseSingleton instance; // we are creating static variable, which will be initialized only once,
		// regardless of how many times we call the function getInstance()
		// From C++ standard 11 this way is thread-safe. It is almost impossible now to run into prior version.
		return instance;
	}
	void use() {
		std::cout << "Using Singleton object" << std::endl;
	}
private:
	BaseSingleton() { std::cout << "Creating Singleton object" << std::endl; };
	BaseSingleton(const BaseSingleton&) = default;
	BaseSingleton& operator=(const BaseSingleton&) = default;
};


int main() {
	BaseSingleton& singleton = BaseSingleton::getInstance();
	singleton.use();
	BaseSingleton::getInstance().use(); 

	return 0;
}