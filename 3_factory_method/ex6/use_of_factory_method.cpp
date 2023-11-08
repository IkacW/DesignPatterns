#include <iostream>
#include <vector>

#define USE_FACTORY_METHOD false

using namespace std;

/* we have abstract calss animal and concrete heritable classes Dog, Fish, Bird, durign execution of program
   we are asked to choose which types of animals we want to create and after that we are showind what created
   animals do.
   In this example we will consider the case when we are using factory method and in the main part of program 
   we will create desired objects 
   USE_FACTORY_METHOD defines if we are using factory method*/
class Animal {
public:
    virtual void move() = 0;
    // static method is playing the role of factory method
    // when USE_FACTORY_METHOD is false, we can imagine that this method does not exist
    static Animal* makeAnimal(int odabir);
};

class Dog: public Animal {
public:
    void move() {
        cout << "Dog: running..." << endl;
    }
};
class Fish: public Animal {
public:
    void move() {
        cout << "Fish: swimming..." << endl;
    }
};
class Bird: public Animal {
public:
    void move() {
        cout << "Bird: Flying..." << endl;
    }
};

/* implementacija fabrickog metoda */
Animal* Animal::makeAnimal(int selection) {
    if (selection == 1) {
        return new Dog();
    }
    else if (selection == 2) {
        return new Fish();
    }
    else {
        return new Bird();
    }
}

int main() {
    vector<Animal*> roles;
    int selection;
    while (true) {
        cout << "Select the role (1-3) or start the simulation(0)\nDog(1), Fish(2), Bird(3), Start(0): ";
        cin >> selection;
        if (selection == 0) {
            break;
        }
        if (USE_FACTORY_METHOD) {
            roles.push_back(Animal::makeAnimal(selection));
        }
        else {
            if (selection == 1) {
                roles.push_back(new Dog());
            }
            else if (selection == 2) {
                roles.push_back(new Fish());
            }
            else {
                roles.push_back(new Bird());
            }
        }
    }
    for (int i = 0; i < roles.size(); i++) {
        roles[i]->move();
    }
    for (int i = 0; i < roles.size(); i++) {
        delete roles[i];
    }
    return 0;
}
