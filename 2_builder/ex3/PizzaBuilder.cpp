#include <iostream>

using namespace std;

/* concrete product */
class Pizza {
private:
    int size;
    int ketchup;
    int cheese;
    int pepper;
    int ham;
public:
    Pizza() {
        size = 10;
        ketchup = 0;
        cheese = 0;
        ham = 0;
        pepper = 0;
    }
    int getSize() { return this->size; }
    void setSize(int size) { this->size = size; }
    int getKetchup() { return this->ketchup; }
    void setKetchup(int ketchup) { this->ketchup = ketchup; }
    int getCheese() { return this->cheese; }
    void setCheese(int cheese) { this->ham = ham; }
    int getHam() { return this->ham; }
    void setHam(int ham) { this->ham = ham; }
    int getPepper() { return this->pepper; }
    void setPeppers(int pepper) { this->pepper = pepper; }
    void show() {
        cout << "Pizza: size(" << size << "), ketchup(" << ketchup << "), " ;
        cout << "cheese(" << cheese << "), ham(" << ham << "), pepper(" << pepper << ")" << endl;
    }
};

/* abstract builder */
class PizzaBuilder {
public:
    virtual PizzaBuilder* setSize(int size) = 0;
    virtual PizzaBuilder* setCheese(int cheese) = 0;
    virtual PizzaBuilder* setKetchup(int ketchup) = 0;
    virtual PizzaBuilder* setHam(int ham) = 0;
    virtual PizzaBuilder* setPeppers(int pepper) = 0;
    virtual Pizza* makePizza() = 0;
};

/* concrete builder */
class PizzaMargaritaBuilder : public PizzaBuilder {
private:
    Pizza *pica;
public:
    PizzaMargaritaBuilder() {
        pica = new Pizza();
    }
    ~PizzaMargaritaBuilder() {
        //delete pica;
    }
    PizzaBuilder* setSize(int size) {
        pica->setSize(size);
        return (PizzaBuilder*) this;
    }
    PizzaBuilder* setCheese(int cheese) {
        pica->setCheese(cheese);
        return (PizzaBuilder*) this;
    }
    PizzaBuilder* setKetchup(int ketchup) {
        pica->setKetchup(ketchup);
        return (PizzaBuilder*) this;
    }
    PizzaBuilder* setHam(int ham) {
        pica->setHam(ham);
        return (PizzaBuilder*) this;
    }
    PizzaBuilder* setPeppers(int pepper) {
        pica->setPeppers(pepper);
        return (PizzaBuilder*) this;
    }

    Pizza* makePizza() {
        return pica;
    }
};

/* controller / director, it is using concrete builder (which is not, in this case, forwarded through 
  constructor) to make/generate concrete product */
class PizzeriaMargarita {
public:
    PizzeriaMargarita() { }
    Pizza *makePizza() {
        PizzaBuilder *picaGraditelj = new PizzaMargaritaBuilder();
        picaGraditelj->setKetchup(5)->setCheese(7)->setHam(8);
        return picaGraditelj->makePizza();

    }
};

/* kreiramo upravljaca i trazimo mu da nam kreira proizvod */
int main() {
    PizzeriaMargarita *picerija = new PizzeriaMargarita();
    Pizza *pica = picerija->makePizza();
    pica->show();

    return 0;
}
