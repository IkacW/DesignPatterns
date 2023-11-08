#include<iostream>

class Warrior {
protected:
	int attack;
	int defence;
public:
	Warrior(): attack(1), defence(1) {}
	Warrior(int attack, int defence): attack(attack), defence(defence) {}
	virtual int strike() const = 0;
	virtual void stikedFor(int attackDamage) = 0;
	virtual ~Warrior() {}
};

/*
We have 2 concrete classes, AttackWarrior and DefensiveWarrior. 
*/
class DefensiveWarrior : public Warrior {
public:
	DefensiveWarrior(int attack, int defence) : Warrior(attack, defence) {}
	int strike() const override { return attack; }
	void stikedFor(int attackDamage) {// Defence warrior can block some percentage of the attack
		attackDamage -= defence;
		attackDamage = 0.9 * attackDamage;
		attackDamage = std::max(0, attackDamage);
		std::cout << "Primljen udarac jacine " << attackDamage << std::endl;
	}
};

class AttackWarrior : public Warrior {
public:
	AttackWarrior(int attack, int defence) : Warrior(attack, defence) {}
	int strike() const override { return attack * 1.1; } // Attack warrior has some 'critical' damage
	void stikedFor(int attackStrength) {
		attackStrength -= defence;
		attackStrength = std::max(0, attackStrength);
		std::cout << "Damage done: " << attackStrength << std::endl;
	}
};

class WarriorWithEquipment : public Warrior {
protected:
	Warrior* decoratedWarrrior;
public:
	WarriorWithEquipment(Warrior* decoratedWarrrior): decoratedWarrrior(decoratedWarrrior) {}
	// We can implement attack and defence methods, and then in derived decoratos to override them
	// if needed (motaivation behind this is that in some cases we dont need to implement both methods).
	int strike() const override { return decoratedWarrrior->strike(); }
	void stikedFor(int attackDamage) override { decoratedWarrrior->stikedFor(attackDamage); }
};

class SwordWarrior : public WarriorWithEquipment {
private:
	int swordDamage;
public:
	SwordWarrior(Warrior* decoratedWarrrior, int swordDamage): WarriorWithEquipment(decoratedWarrrior), swordDamage(swordDamage) {}
	int strike() const override {
		int attackBaseDamage = decoratedWarrrior->strike();
		return swordDamage + attackBaseDamage;
	}
	// defence is not overrided because there is no need for it. Attack warrior has only larger damage 
	// which is given by the sword. 
};

class ShieldWarrior : public WarriorWithEquipment {
private:
	int shieldDamageReduction;
public:
	ShieldWarrior(Warrior* decoratedWarrrior, int shieldDamageReduction): 
		WarriorWithEquipment(decoratedWarrrior), shieldDamageReduction(shieldDamageReduction) {}
	void stikedFor(int attackDamage) override {
		attackDamage -= shieldDamageReduction;
		decoratedWarrrior->stikedFor(attackDamage);
	}
	// no need to overrirde attack method.. 
};

class ArmourWarrior : public WarriorWithEquipment {
private:
	int armourStrength;
public:
	ArmourWarrior(Warrior* decoratedWarrrior, int armourStrength) :
		WarriorWithEquipment(decoratedWarrrior), armourStrength(armourStrength) {}
	// Armour is heavy, that is why base attack damage is lower, he's putting more effort into strike. 
	// Here we will override both methods.  
	void stikedFor(int attackDamage) override {
		attackDamage -= armourStrength;
		decoratedWarrrior->stikedFor(attackDamage);
	}
	int strike() const override {
		int baseAttackDamage = decoratedWarrrior->strike();
		return baseAttackDamage - 0.1 * armourStrength;
	}
};

int main() {
	Warrior* r = new DefensiveWarrior(10, 8);
	Warrior* r2 = new ShieldWarrior(new ArmourWarrior(new SwordWarrior(new AttackWarrior(10, 10), 5), 10), 4);
	
	std::cout << "Defence warrior attack damage is: " << r->strike() << std::endl;
	std::cout << "Damage delt to defence warrior is: " << std::endl;
	r->stikedFor(10);

	std::cout << "Warrior with equipment attack damage is: " << r2->strike() << std::endl;
	std::cout << "Damage delt to warrior with equipment is: " << std::endl;
	r2->stikedFor(10);

	return 0;
}