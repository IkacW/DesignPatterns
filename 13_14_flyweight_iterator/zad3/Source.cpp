#include<iostream>
#include<vector>
#include<tuple>

class GraphicElement {
public:
	virtual void draw(int x, int y, int angle) = 0;
	virtual ~GraphicElement() {}
};

class Tree : public GraphicElement {
protected:
	std::string texturePath;
public:
	Tree(const std::string& path): texturePath(path) {}
};

class Oak : public Tree {
public:
	Oak() : Tree("models/oak.obj") {}
	void draw(int x, int y, int angle) override {
		std::cout << "Drawing oak" << texturePath << " [" << x << ", " << y << "], angle = " << angle << std::endl;
	}
};

class Spruce : public Tree {
public:
	Spruce() : Tree("models/spruce.obj") {}
	void draw(int x, int y, int angle) override {
		std::cout << "Drawing Spruce" << texturePath << " [" << x << ", " << y << "], angle = " << angle << std::endl;
	}
};

class Animal : public GraphicElement {
protected:
	std::string texturePath;
public:
	Animal(const std::string& path) : texturePath(path) {}
};

class Bear : public Animal {
public:
	Bear() : Animal("models/bear.obj") {}
	void draw(int x, int y, int ugao) override {
		std::cout << "Drawing bear" << texturePath << " [" << x << ", " << y << "], angle = " << ugao << std::endl;
	}
};

class Wolf : public Animal {
public:
	Wolf() : Animal("models/wolf.obj") {}
	void draw(int x, int y, int angle) override {
		std::cout << "Drawing wolf" << texturePath << " [" << x << ", " << y << "], angle = " << angle << std::endl;
	}
};

class Ecosystem { 
	// This class is playing the role of the factory of living organisms, but we can't mix other
	// organisms, because of that we will organize it like abstract factory.
protected:
	Ecosystem() {};
	Ecosystem& operator=(const Ecosystem& copy) = default;
	Ecosystem(const Ecosystem& copy) = default;
public:
	virtual Animal* getAnimal() = 0;
	virtual Tree* getTree() = 0;
	virtual ~Ecosystem() {}
};

class EcosystemOfDeciduousTrees : public Ecosystem {
private:
	EcosystemOfDeciduousTrees() = default;
	EcosystemOfDeciduousTrees& operator=(const EcosystemOfDeciduousTrees& copy) = default;
	EcosystemOfDeciduousTrees(const EcosystemOfDeciduousTrees& copy) = default;

	// Because all ,for example, bears will have same internal state, and only diferentiate by coordinates
	// where they are at given time, we will store coordinates in external 'storage' and with that we need 
	// only one instace of bear. 
	Bear* bear = nullptr;
	Oak* hrast = nullptr;
public:
	static Ecosystem& getInstance() {
		static EcosystemOfDeciduousTrees instance;
		return instance;
	}

	Animal* getAnimal() override {
		if (!bear) bear = new Bear();
		return bear;
	}

	Tree* getTree() override {
		if (!hrast) hrast = new Oak();
		return hrast;
	}

	~EcosystemOfDeciduousTrees() {
		delete bear;
		delete hrast;
	}
	
};


class EcosystemOfConiferTrees : public Ecosystem {
private:
	EcosystemOfConiferTrees() = default;
	EcosystemOfConiferTrees& operator=(const EcosystemOfConiferTrees& copy) = default;
	EcosystemOfConiferTrees(const EcosystemOfConiferTrees& copy) = default;

	Wolf* wolf = nullptr;
	Spruce* spruce = nullptr;
public:
	static Ecosystem& getInstance() {
		static EcosystemOfConiferTrees instance;
		return instance;
	}

	Animal* getAnimal() override {
		if (!wolf) wolf = new Wolf();
		return wolf;
	}

	Tree* getTree() override {
		if (!spruce) spruce = new Spruce();
		return spruce;
	}

	~EcosystemOfConiferTrees() {
		delete spruce;
		delete wolf;
	}
};

class Forest : public GraphicElement {
protected:
	int width;
	int length;
	// Trees are going to be stored in the matrix. Position of every tree is stored like an index of 
	// row and comlumn of the matrix, but we need to sotre an angle too, that will be stored in the separate 
	// matix, where the tree is stored in first matrix at that field, in second matrix, angle will be storeda
	// We could also store the internal state of an object in a wrapper class, which would have an poninter 
	// to an object that is representing internal state
	std::vector<std::vector<Tree*>> trees;
	std::vector<std::vector<int>> treesAngle;
	// Because we have smaller group of animals, we will be storing external state like ordered triplet
	// (x, y, angle).
	std::vector<Animal*> animals;
	std::vector<std::tuple<int, int, int>> pos_angle;

public:
	Forest() = default;
	Forest(int length, int width) : length(length), width(width) {
		trees = std::vector<std::vector<Tree*>>(length);
		treesAngle = std::vector<std::vector<int>>(length);
		for (int i = 0; i < length; i++) {
			trees[i] = std::vector<Tree*>(width);
			treesAngle[i] = std::vector<int>(width);
		}
	}
	void draw(int x, int y, int angle) {
		for (int i = 0; i < trees.size(); i++) {
			for (int j = 0; j < trees[i].size(); j++) {
				trees[i][j]->draw(x + j, y + i, (angle + treesAngle[i][j]) % 360);
			}
		}
		for (int i = 0; i < animals.size(); i++) {
			int pos_x = std::get<0>(pos_angle[i]);
			int pos_y = std::get<1>(pos_angle[i]);
			int _angle = std::get<2>(pos_angle[i]);

			animals[i]->draw(x + pos_x, y + pos_y, angle + _angle);
		}
	}
};

class DeciduousForest : public Forest {
public:
	typedef EcosystemOfDeciduousTrees ForestEcosystem;

	DeciduousForest(int length, int width): Forest(length, width) {
		
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < width; j++) {
				trees[i][j] = ForestEcosystem::getInstance().getTree();
				treesAngle[i][j] = rand() % 360;
			}
		}
		int numberOfAnimals = length * width / 5;
		for (int i = 0; i < numberOfAnimals; i++) {
			animals.push_back(ForestEcosystem::getInstance().getAnimal());
			pos_angle.push_back(
				std::make_tuple<int, int, int>(rand() % width, rand() % length, rand() % 360));
		}
	}
};

int main() {
	Forest* forest = new DeciduousForest(5, 5);
	forest->draw(0, 0, 0);
	return 0;
}
