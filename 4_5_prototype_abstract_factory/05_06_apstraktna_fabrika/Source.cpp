#include<iostream>

/*
5. Crete abstract classes Table, Chair and Shelf and also 
concrete classes WoodenTable, WoodenChair, WoodenShelf, ModernTable, ModernChair, ModernShelf
as well as factories for this two famillies of products.
6. Create class Room which has table, chair and shelf. Room has to by created by object of class Designer
in a way:
Room r = designer.createRoom(style);
We can have two builders which will create room choosing the furniture from chosen factory
(first builder is using one factory while second builder is using other factory). Designer is playing the role
of director/controller. If we have concrete builders which we create based on a room style (enum or string)
then we also have the use of factory method which will create builder.
Question: Could we clone a room? Are there any setbacks to it?
*/

class ITable {
public:
	virtual void description() = 0;
	virtual ~ITable() {};
};

class WoodenTable : public ITable {
public:
	void description() override {
		std::cout << "Wooden Table" << std::endl;
	}
};

class ModernTable : public ITable {
public:
	void description() override {
		std::cout << "Modern Table" << std::endl;
	}
};

class IChair {
public:
	virtual void description() = 0;
	virtual ~IChair() {}
};

class WoodenChair : public IChair {
public:
	void description() override {
		std::cout << "Wooden Chair" << std::endl;
	}
};

class ModernChair : public IChair {
public:
	void description() override {
		std::cout << "Modern Chair" << std::endl;
	}
 };

class IShelf {
public:
	virtual void description() = 0;
	virtual ~IShelf() {}
};

class WoodenShelf : public IShelf {
public:
	void description() override {
		std::cout << "Wooden Shelf" << std::endl;
	}
};

class ModernShelf : public IShelf {
public:
	void description() override {
		std::cout << "Modern Shelf" << std::endl;
	}
};

class IFurnitureFactory {
public:
	virtual IChair* makeChair() = 0;
	virtual ITable* makeTable() = 0;
	virtual IShelf* makeShelf() = 0;
	virtual ~IFurnitureFactory() {}
};

class WoodenFurnitureFactory : public IFurnitureFactory {
public:
	IChair* makeChair() override { return new WoodenChair(); }
	ITable* makeTable() override { return new WoodenTable(); }
	IShelf* makeShelf() override { return new WoodenShelf(); }
};

class ModernFurnitureFactory : public IFurnitureFactory {
public:
	IChair* makeChair() override { return new ModernChair(); }
	ITable* makeTable() override { return new ModernTable(); }
	IShelf* makeShelf() override { return new ModernShelf(); }
};


class Room {
private:
	ITable* table;
	IShelf* chair;
	IChair* shelf;
public:
	void setTable(ITable* table) { this->table = table; }
	void setChair(IChair* shelf) { this->shelf = shelf; }
	void setShelf(IShelf* chair) { this->chair = chair; }
	void description() {
		std::cout << "Room description: " << std::endl;
		table->description();
		shelf->description();
		chair->description();
	}
};

enum class RoomStyle {WOODEN, MODERN};

class IRoomBuilder {
protected:
	Room* room;
public:
	IRoomBuilder& createEmptyRoom() {
		room = new Room();
		return *this;
	}
	virtual IRoomBuilder& setTable() = 0;
	virtual IRoomBuilder& setChair() = 0;
	virtual IRoomBuilder& setShelf() = 0;
	virtual ~IRoomBuilder() {}
	Room* getRoom() { return room; }
	static IRoomBuilder* createBuilder(RoomStyle style);
};

class WoodenRoomBuilder: public IRoomBuilder {
private:
	WoodenFurnitureFactory factory;
public:
	IRoomBuilder& setTable() override {
		room->setTable(factory.makeTable());
		return *this;
	}
	IRoomBuilder& setChair() override {
		room->setChair(factory.makeChair());
		return *this;
	}
	IRoomBuilder& setShelf() override {
		room->setShelf(factory.makeShelf());
		return *this;
	}
};

class ModernRoomBuilder : public IRoomBuilder {
private:
	ModernFurnitureFactory factory;
public:
	IRoomBuilder& setTable() override {
		room->setTable(factory.makeTable());
		return *this;
	}
	IRoomBuilder& setChair() override {
		room->setChair(factory.makeChair());
		return *this;
	}
	IRoomBuilder& setShelf() override {
		room->setShelf(factory.makeShelf());
		return *this;
	}
};

IRoomBuilder* IRoomBuilder::createBuilder(RoomStyle style) {
	if (style == RoomStyle::WOODEN) return new WoodenRoomBuilder();
	return new ModernRoomBuilder();
}

class Designer {
public:
	Room* createRoom(RoomStyle style) {
		IRoomBuilder* builder = IRoomBuilder::createBuilder(style);
		builder->createEmptyRoom().setShelf().setTable().setChair();
		Room* room = builder->getRoom();
		delete builder;
		return room;
	}
};

int main() {
	Designer designer;
	Room* r1 = designer.createRoom(RoomStyle::WOODEN);
	Room* r2 = designer.createRoom(RoomStyle::MODERN);
	r1->description();
	std::cout << std::endl;
	r2->description();

	return 0;
}
