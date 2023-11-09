#pragma once
#include<iostream>
#include<unordered_map>

class Kontekst {
private:
	std::unordered_map<std::string, bool> vrednosti;
public:
	bool value(std::string kljuc) {
		return vrednosti[kljuc];
	}
	bool& operator[] (std::string kljuc) { return vrednosti[kljuc]; }
	friend std::ostream& operator << (std::ostream& stream, Kontekst k) {
		for (auto it = k.vrednosti.begin(); it != k.vrednosti.end(); it++) {
			stream << it->first << ": " << it->second << "\n";
		}
		stream << std::endl;
		return stream;
	}
};

class LogickiIzraz {
public:
	virtual bool interpretiraj(Kontekst&) const = 0;
	virtual ~LogickiIzraz() {}
	virtual void ispisi() const = 0; 
};

class Konstanta : public LogickiIzraz {
private:
	bool value;
public:
	Konstanta(bool value) : value(value) {}
	bool interpretiraj(Kontekst&) const override { return value; }
	void ispisi() const override { std::cout << value; } 
	friend std::ostream& operator << (std::ostream& stream, const Konstanta& k) { stream << k.value; return stream; }
};

class Promenljiva : public LogickiIzraz {
private:
	std::string first_name;
public:
	Promenljiva(const std::string& first_name) : first_name(first_name) {}
	bool interpretiraj(Kontekst& kontekst) const override {
		return kontekst.value(first_name);
	}
	friend std::ostream& operator << (std::ostream& stream, const Promenljiva& p) { stream << p.first_name; return stream; }
	void ispisi() const override { std::cout << first_name; }
};


template<typename LevaFormula, typename DesnaFormula>
class LogickoIli : public LogickiIzraz {
private:
	LevaFormula leva;
	DesnaFormula desna;
public:
	LogickoIli(const LevaFormula& leva, const DesnaFormula& desna) :
		leva(leva), desna(desna) {}
	bool interpretiraj(Kontekst& kontekst) const override {
		return leva.interpretiraj(kontekst) || desna.interpretiraj(kontekst);
	}
	friend std::ostream& operator << (std::ostream& stream, const LogickoIli& ili) {
		stream << "OR(" << ili.leva << ", " << ili.desna << ")";
		return stream;
	}

	void ispisi() const override {
		std::cout << *this;
	}
};

template<typename LevaFormula, typename DesnaFormula>
class LogickoI : public LogickiIzraz {
private:
	LevaFormula leva;
	DesnaFormula desna;
public:
	LogickoI(const LevaFormula& leva, const DesnaFormula& desna) :
		leva(leva), desna(desna) {}
	bool interpretiraj(Kontekst& kontekst) const override {
		return leva.interpretiraj(kontekst) && desna.interpretiraj(kontekst);
	}
	friend std::ostream& operator << (std::ostream& stream, const LogickoI& i) {
		stream << "AND(" << i.leva << ", " << i.desna << ")";
		return stream;
	}

	void ispisi() const override {
		std::cout << *this;
	}
};

template<typename Formula>
class Negacija : public LogickiIzraz {
private:
	Formula formula;
public:
	Negacija(const Formula& formula) : formula(formula) {}
	bool interpretiraj(Kontekst& kontekst) const override {
		return !formula.interpretiraj(kontekst);
	}
	friend std::ostream& operator << (std::ostream& stream, const Negacija& n) {
		stream << "NOT(" << n.formula << ")";
		return stream;
	}

	void ispisi() const override {
		std::cout << *this;
	}
};