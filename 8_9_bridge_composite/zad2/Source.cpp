#include<iostream>
#include<vector>

class TitleFile {
protected:
	std::string filename;
public:
	std::string getFilename() { return filename; }
	TitleFile(const std::string& filename) : filename(filename) {}
	virtual std::vector<std::tuple<int, int, std::string>*> parseFile() = 0;
	// Lets say that we simulate work of these classes with parseFile that returns 
	// ordered triples (from, to, subtitle) that defines what is displaying on screen 
	// at given period of time
	virtual ~TitleFile() {}
};

class SrtTitle : public TitleFile {
public:
	// For class SrtTitle we would nees constructor with one parameter
	// (const std::string&) just to be able to pass it to the constructor of base class
	// Instead of that we can use in this following way base constructor.
	using TitleFile::TitleFile;

	std::vector<std::tuple<int, int, std::string>*> parseFile() {
		std::cout << "Opening file " + filename + " with srt subtitle..." << std::endl;
		return std::vector<std::tuple<int, int, std::string>*>();
	}
};

class SubTitle : public TitleFile {
public:
	using TitleFile::TitleFile;

	std::vector<std::tuple<int, int, std::string>*> parseFile() {
		std::cout << "Opening file " + filename + " with sub subtitle..." << std::endl;
		return std::vector<std::tuple<int, int, std::string>*>();
	}
};

class TxtTitle : public TitleFile {
public:
	using TitleFile::TitleFile;

	std::vector<std::tuple<int, int, std::string>*> parseFile() {
		std::cout << "Opening file " + filename + " with txt subtitle..." << std::endl;
		return std::vector<std::tuple<int, int, std::string>*>();
	}
};

class TitleDisplay {
protected:
	int fontSize = 14;
	std::string fontStyle = "Times New Roman";
	TitleFile* titleFile;
	std::vector<std::tuple<int, int, std::string>*> subtitles;

	void parseFile() {
		// Parsing is left for implementator.
		// It is important to separate abstraction from implementation.
		std::cout << "Parsing " << titleFile->getFilename() << std::endl;
		subtitles = titleFile->parseFile();
	};
public:
	TitleDisplay(TitleFile* titleFile): 
		titleFile(titleFile) {
		parseFile();
	}
	virtual void displaySubtitle() {
		std::cout << "Showing basic subtitles" << std::endl;
	}
};

class PremiumTitleDisplay : public TitleDisplay {
public:
	// Regardless of the attributes this class possesses, parsing is the same and it's done by the implementator.
	PremiumTitleDisplay(TitleFile* file, int fontSize, const std::string& fontStyle) : TitleDisplay(file) {
		this->fontSize = fontSize;
		this->fontStyle = fontStyle;
	}
	void displaySubtitle() override {
		std::cout << "Showing premium subtitle with fontSize = " << fontSize;
		std::cout << ", fontStyle = " << fontStyle << std::endl;
	}
};

int main() {
	TitleDisplay* t1 = new TitleDisplay(new SrtTitle("title.srt"));
	TitleDisplay* t2 = new PremiumTitleDisplay(new TxtTitle("title2.txt"), 14, "Arial");

	t1->displaySubtitle();
	t2->displaySubtitle();
	
	return 0;
}
