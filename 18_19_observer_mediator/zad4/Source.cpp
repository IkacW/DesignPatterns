#include<iostream>
#include<unordered_map>

class Bank;

class Account {
protected:
	std::string accountNumber; 
	float balance;
	Bank* bank;
public:
	float getBalance() const { return balance; }
	std::string getAccountNumber() const { return accountNumber; }
	Account(Bank* bank, const std::string& accountNumber, int balance);

	virtual void makeTransaction(const std::string& toAccount, int amount) = 0;
	void receivePayment(std::string fromAccount, float amount) {
		std::cout << "From account" << fromAccount << " you received " << amount << " " << this->currency() << "\n";
		balance += amount; 
	}
	virtual std::string currency() const = 0;
};

class Bank {
	std::unordered_map<std::string, Account*> accounts;
	std::vector<std::string> blockedAccounts;
public:
	virtual float commission(float amount) const = 0; 

	void addAccount(Account* r) {
		accounts[r->getAccountNumber()] = r;
	}
	float makeTransaction(std::string fromAccount, std::string toAccount, int amount) {
		for (int i = 0; i < blockedAccounts.size(); i++)
			if (blockedAccounts[i] == fromAccount) return 0;
		if (accounts.find(fromAccount) == accounts.end() || accounts.find(toAccount) == accounts.end()) return 0;
		Account* from = accounts[fromAccount];
		Account* to = accounts[toAccount];
		float _amount;
		if (from->currency() == to->currency()) {
			_amount = amount;
		}
		else {
			if (from->currency() == "din") {
				// Converting rsd to usd
				_amount = amount / 119.0f;
			}
			else {
				// converting usd to rsd
				_amount = amount * 117;
			}
		}
		to->receivePayment(fromAccount, _amount);
		float wholeAmount = amount + commission(amount);  
		// We are calling commission function, but we are sure that function exists because we must implement
		// it in derived classes.
		if (wholeAmount <= from->getBalance())
			return wholeAmount;
		else 
			return 0;
	}
};

class BankA : public Bank {
public:
	// We could make this more interesting, for example we could make commission differ based on amount 
	// that is transfering.

	// It is not good to gave multiple classes which differ only in one method, it is better here
	// to use strategy for calculatin commission.
	// We have two derived classes only because we want to show that we can have multiple mediators(this case 
	// banks), not only one, and also multiple coleagues(accounts)
	
	float commission(float amount) const override { return 0.01 * amount; }
};

class BankB : public Bank {
public:
	float commission(float amount) const override { return 0.02 * amount; }
};

class RsdAccount : public Account {
public:
	using Account::Account;
	std::string currency() const override { return "din"; }
	void makeTransaction(const std::string& toAccount, int amount) {
		float totalAmount = bank->makeTransaction(accountNumber, toAccount, amount);
		if (totalAmount == 0) {
			std::cout << "Failed to transfer " << amount << " rsd to account " << toAccount << "\n";
		}
		else {
			std::cout << "You have successfully transfered " << amount << " rsd to account " << toAccount << "\n";
			std::cout << "The balance is reduced by " << totalAmount << " " << this->currency() << std::endl;
			balance -= totalAmount;
		}
	}
};

class EurAccount : public Account {
public:
	using Account::Account;
	std::string currency() const override { return "eur"; }
	void makeTransaction(const std::string& toAccount, int amount) {
		float totalAmount = bank->makeTransaction(accountNumber, toAccount, amount);
		if (totalAmount == 0) {
			std::cout << "Failed to transfer " << amount << " eur to account " << toAccount << "\n";
		}
		else {
			std::cout << "You have successfully transfered " << amount << " eur to account " << toAccount << "\n";
			std::cout << "The balance is reduced by " << totalAmount << " " << this->currency() << std::endl;
			balance -= totalAmount;
		}
	}
};

Account::Account(Bank* bank, const std::string& accountNumber, int balance) :
	bank(bank), accountNumber(accountNumber), balance(balance) {
	bank->addAccount(this); 
	// We are 'creating' account in bank immidiately (because we passed throught constructor desired bank), 
	// It would be bad to crete store account independently after creting accouunt.
	
	// The more correct way of solving this problem is that we make the class bank factory of accounts too.
	// Banks would be able to be unique account number, as in real life.
}

int main() {
	Bank* b = new BankA();
	Account* r1 = new RsdAccount(b, "123", 1241);
	Account* r2 = new EurAccount(b, "321", 241);
	r2->makeTransaction("123", 100);
	return 0;
}
