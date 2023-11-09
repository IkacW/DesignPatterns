#include<iostream>
#include<fstream>
#include<sstream>
#include<queue>
#include<stack>

class Document {
private:
	std::string content;
	std::string file_name;
public:
	Document(const std::string& file_name): file_name(file_name) {
		std::ifstream file(file_name);
		if (file.is_open()) { // If file exists, we will read it.
			std::stringstream stream;
			stream << file.rdbuf();
			content = stream.str();
			file.close();
		}
		else 
			content = "";
	}
	void save() {
		std::ofstream fajl(file_name);
		fajl << content;
		fajl.close();
	}
	void inputChar(char c, int pos) {
		content.insert(pos, 1, c);
	}
	void addChar(char c) {
		content += c;
	}
	std::string getContent() const { return content; }
	void setContent(std::string content) { this->content = content; }
};

class Command {
protected:
	Document* d;
public:
	Command(Document* d): d(d) {}
	virtual void execute() = 0;
	virtual void undo() = 0; // we will enable undo command
	virtual ~Command() {}
};

class Save : public Command {
public:
	using Command::Command;
	void execute() override { d->save(); }
	void undo() override { }; // we can not undo a save 
};

class AddCharacter : public Command {
private:
	char c;
public:
	AddCharacter(Document* d, char c): Command(d), c(c) {}
	void execute() override { d->addChar(c); }
	void undo() override {
		std::string content = d->getContent();
		content = content.substr(0, content.size() - 1);
		d->setContent(content);
	}
};

class InputCharacter : public Command {
private:
	char c;
	int pos;
public:
	InputCharacter(Document* d, char c, int pos) : Command(d), c(c), pos(pos) {}
	void execute() override { d->inputChar(c, pos); }
	void undo() override {
		// Not the most effective way of deleting character from a string at specified position, 
		// but effectiveness is not the focus in this example.
		std::string content = d->getContent();
		content = content.substr(0, pos) + content.substr(pos + 1);
		d->setContent(content);
	}
};

class Invoker { // Invoker
private:
	std::queue<Command*> commands; 
	// We need to use queue so we know the order of executing commands.

	// To make commands undo and redo possible to execute, we will will use two stacks. Whenever we execute
	// some command, we will add it to an udno Stack, which will be used to implement undo function.
	// In redoStack we will add the command whenever we call the undo function. 
	// When user use undo command, and then do a new command, we must make sure that he can't redo command.
	std::stack<Command*> undoStack;
	std::stack<Command*> redoStack;
public:
	void addCommand(Command* komanda) {
		commands.push(komanda);
	}
	void executeCommand(Command* komanda) {
		komanda->execute();
		undoStack.push(komanda);
		while (redoStack.size() > 0) { redoStack.pop(); } // redo can not be executed after executing 
		//command that is not an undo command
	}
	void executeCommands() {
		while (commands.size() > 0) {
			Command* k = commands.front();
			commands.pop();
			executeCommand(k);
		}
	}
	void undo() {
		if (undoStack.size() > 0) {
			Command* k = undoStack.top();
			undoStack.pop();
			k->undo();
			redoStack.push(k);
		}
	}
	void redo() {
		if (redoStack.size() > 0) {
			Command* k = redoStack.top();
			redoStack.pop();
			k->execute();
			undoStack.push(k);
		}
	}
};

int main() {
	Document* d = new Document("test.txt");
	Invoker p;
	p.addCommand(new AddCharacter(d, 'a'));
	p.addCommand(new AddCharacter(d, 'b'));
	p.addCommand(new AddCharacter(d, 'd'));
	p.addCommand(new AddCharacter(d, 'e'));
	p.addCommand(new AddCharacter(d, 'f'));
	p.addCommand(new InputCharacter(d, 'c', 2));
	p.executeCommands();
	p.executeCommand(new Save(d));
	std::cout << "Document content: " << d->getContent() << std::endl;

	for (int i = 0; i < 7; i++) {
		p.undo();
		std::cout << "Document content: " << d->getContent() << std::endl;
	}
	return 0;
}


