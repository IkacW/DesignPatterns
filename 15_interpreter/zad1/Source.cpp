#include<iostream>
#include"LogickiIzrazi.h"

/*
We chose the approach where we will create logical expressions with functions AND, OR, NOT
that return certan nonterminal logical expressions.
With the use of templates we enable use of the desired behaviour and clean code (nowhere in program
(main function) we won't use explicit creation of classes LogicExpression (we won't have an messy code like
LogicalExpression* expression = new LogicalAnd(new LogicalOr(new Not(new Variable("x")), new Constant(true)),
new Variable("y"));
Instead of that, we will make it possible for more practical code declaration, and more readable one like:
auto izraz = AND(OR(NOT(Variable("x")), Constant(true)), Variable("y"));
We will go one step further, and we will it possible to use even more pratical line of code like:
auto izraz = AND(OR(NOT("x"), true), "y")
*/

// Function AND will creato object of type LogicalAnd. 
// Take a look at the file LogickiIzrazi.h!
// LogicalAnd is template class and it depends on two parameters: left and right formula. 
// Both classes (formulas) must have impelmented methods: interpret(Context&) and operator <<.
// We want to make it possible to call fucntion AND even when some of operands are string or bool.
// When the operand is bool we wanna treat it as a constant, and string as a variable. 
// If we have a line like AND(true, "x") at the moment of compiling, that line will instance function
// AND<bool, const char*>, međutim ono što treba da vratimo kao rezultat functions NIJE tipa
// LogickoI<bool, const char*> - to bi bili nevalidni parametri šablona (ne postoji metoda interpretiraj
// za promenljivu tipa bool ili const char*).
// Očekivani tip rezultata bi zapravo bio LogickoI<Konstanta, Promenljiva>. 
// Isto tako mogli bismo pozvati AND sa AND(true, true) ili AND(OR("x", "y"), NOT("z")) pri čemu su
// odgovarajući tipovi rezultata LogickoI<Konstanta, Konstanta> i 
// LogickoI<LogickoIli<Promenljiva, Promenljiva>, Negacija<Promenljiva>>, a functions koje vrše poziv
// AND<bool, bool> i AND<LogickoIli<Promenljiva, Promenljiva>, Negacija<Promenljiva>>. 
// U drugom slučaju vidimo da je tip rezultata poziva functions AND<L, R> tipa LogickoI<L, R>, ali
// da to ne važi za sve slučajeve (važi samo kada su i L i R formule, a ne const char* ili bool).
// Tipičan, staromodni, način da razrešimo ovu situaciju je specijalizacijom šablona functions. 
// Da sami "ručno" ispišemo sve moguće functions za slučajeve kada je neki od operanada bool, kada je neki
// const char* ili formula. Dva operanda, tri mogućnosti za svaki, daju ukupno 9 različitih funkcija koje bismo
// morali da pišemo, tj. imali bismo četiri specijalizacije, četiri parcijalne specijalizacije i jedan šablon
// sa oba parametra.
// Srećom, od C++-a 14 kao rezultat functions možemo navesti ključnu reč auto ukoliko je moguće u vreme kompajliranja
// odrediti tip podatka koji se vraća kao rezultat functions. 
// OD C++-a 17 moguće je korišćenje konstantnih izraza za uslovno grananje. Konstantni izrazi se zapisuju sa
// constexpr(izraz), pri čemu izraz mora biti izraz čija je vrednost poznata u vreme kompajliranja. 
// Kombinovanjem constexpr za grananje i ključne reči auto, kao i utvrđivanjem da li je neki od tipova Leva i Desna
// bool ili const char* mi možemo imati različite grane koje vraćaju različite tipove podataka. To ne znači da će
// zaista jedna funkcija vraćati više tipova, već će se za svaku granu instancirati po jedna funkcija.
// Praktično, rezultat je isti kao da smo ispisali 9 funkcija (šablona/percijalnih i potpunih specijalizacija),
// ali imamo samo jedan šablon (doduše, ipak imamo grananje na 9 slučajeva, od toga ne možemo da pobegnemo).
template<typename Leva, typename Desna>
auto AND(const Leva leva, const Desna desna) {
	if constexpr(std::is_same<Leva, bool>::value) {
		// Ako je tip Leva bool, onda kao levi operand treba da postavimo konstantu, a zatim ispitamo 
		// sve moguće vrednosti za desni tip. I tako dalje za sve slučajeve...
		if constexpr (std::is_same<Desna, bool>::value) {
			return LogickoI<Konstanta, Konstanta>(Konstanta(leva), Konstanta(desna));
		}
		else if constexpr (std::is_same<Desna, const char*>::value) {
			return LogickoI<Konstanta, Promenljiva>(Konstanta(leva), Promenljiva(desna));
		}
		else {
			return LogickoI<Konstanta, Desna>(Konstanta(leva), desna);
		}
	}
	else if constexpr (std::is_same<Leva, const char*>::value) {
		if constexpr (std::is_same<Desna, bool>::value) {
			return LogickoI<Promenljiva, Konstanta>(Promenljiva(leva), Konstanta(desna));
		}
		else if constexpr (std::is_same<Desna, const char*>::value) {
			return LogickoI<Promenljiva, Promenljiva>(Promenljiva(leva), Promenljiva(desna));
		}
		else {
			return LogickoI<Promenljiva, Desna>(Promenljiva(leva), desna);
		}
	}
	else {
		if constexpr (std::is_same<Desna, bool>::value) {
			return LogickoI<Leva, Konstanta>(leva, Konstanta(desna));
		}
		else if constexpr (std::is_same<Desna, const char*>::value) {
			return LogickoI<Leva, Promenljiva>(leva, Promenljiva(desna));
		}
		else {
			// Naravno, ovaj opšti slučaj pokriva sve slučajeve kada ni Leva ni Desna nisu ni const char*, ni bool.
			return LogickoI<Leva, Desna>(leva, desna);
		}
	}
}


// Sada sve isto radimo za šablon functions OR koja treba da kreira odgovarajući objekat LogickoIli<...,...>
template<typename Leva, typename Desna>
auto OR(const Leva leva, const Desna desna) {
	if constexpr (std::is_same<Leva, bool>::value) {
		if constexpr (std::is_same<Desna, bool>::value) {
			return LogickoIli<Konstanta, Konstanta>(Konstanta(leva), Konstanta(desna));
		}
		else if constexpr (std::is_same<Desna, const char*>::value) {
			return LogickoIli<Konstanta, Promenljiva>(Konstanta(leva), Promenljiva(desna));
		}
		else {
			return LogickoIli<Konstanta, Desna>(Konstanta(leva), desna);
		}
	}
	else if constexpr (std::is_same<Leva, const char*>::value) {
		if constexpr (std::is_same<Desna, bool>::value) {
			return LogickoIli<Promenljiva, Konstanta>(Promenljiva(leva), Konstanta(desna));
		}
		else if constexpr (std::is_same<Desna, const char*>::value) {
			return LogickoIli<Promenljiva, Promenljiva>(Promenljiva(leva), Promenljiva(desna));
		}
		else {
			return LogickoIli<Promenljiva, Desna>(Promenljiva(leva), desna);
		}
	}
	else {
		if constexpr (std::is_same<Desna, bool>::value) {
			return LogickoIli<Leva, Konstanta>(leva, Konstanta(desna));
		}
		else if constexpr (std::is_same<Desna, const char*>::value) {
			return LogickoIli<Leva, Promenljiva>(leva, Promenljiva(desna));
		}
		else {
			return LogickoIli<Leva, Desna>(leva, desna);
		}
	}
}

// Za negaciju imamo znatno manje posla... Samo 3 slučaja.
template<typename Formula>
auto NOT(Formula formula) {
	if constexpr (std::is_same<Formula, bool>::value) {
		return Negacija<Konstanta>(Konstanta(formula));
	}
	else if constexpr (std::is_same<Formula, const char*>::value) {
		return Negacija<Promenljiva>(Promenljiva(formula));
	} 
	else { return Negacija<Formula>(formula); }
}


int main() {
	Kontekst k1;
	k1["x"] = true;
	k1["y"] = true;
	k1["z"] = false;

	Kontekst k2;
	k2["x"] = true;
	k2["y"] = false;
	k2["z"] = false;

	// Prelaskom mišem preko ključne reči auto Visual Studio će vam pokazati kog je tačno tipa 
	// promenljiva izraz. U slučaju linije ispod, odgovarajući tip je:
	// LogickoI<LogickoIli<LogickoI<LogickoI<Konstanta, Negacija<Promenljiva>>, Promenljiva>, Promenljiva>, Promenljiva>,
	auto izraz = AND(OR(AND(AND(true, NOT("z")), "x"), "x"), "y");

	bool v1 = izraz.interpretiraj(k1);
	bool v2 = izraz.interpretiraj(k2);

	std::cout << "Vrednost izraza " << izraz << " u kontekstu: \n" << k1 << v1 << std::endl;
	std::cout << "Vrednost izraza " << izraz << " u kontekstu: \n" << k2 << v2 << std::endl;
}