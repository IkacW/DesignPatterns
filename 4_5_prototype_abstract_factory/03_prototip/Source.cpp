#include<iostream>
#include<unordered_map>

/*
Create class Paragaph which has text, fontSize, fontStyle, alignment and indent. Paragraph
can be created throught constructor (with all atributes needed), it should be possible to 
register new paragraph style and later easy generation paragraph of same style.For example, 
we could create paragraph p like:
Paragraph* p = new Paragraph(…);
and state:
registerParagraph(„my style“, p);
If we later need paraph with same setting that we used for paragraph p
we could simply state:
Paragraph* p2 = getParagraph(“my style”);
p2->setText(“Tekst novog paragrafa”);
*/

enum class Alignment { LEFT, RIGHT, CENTER, JUSTIFY };
enum class FontStyle { TIMES_NEW_ROMAN, ARIAL, CALIBRI };

std::ostream& operator << (std::ostream& s, const Alignment alignment) {
	switch (alignment) {
	case Alignment::CENTER:
		return s << "CENTER";
	case Alignment::JUSTIFY:
		return s << "JUSTIFY";
	case Alignment::RIGHT:
		return s << "RIGHT";
	default:
		return s << "LEFT";
	}
}

std::ostream& operator << (std::ostream& s, const FontStyle font) {
	switch (font) {
	case FontStyle::ARIAL:
		return s << "Arial";
	case FontStyle::CALIBRI:
		return s << "Calibri";
	default:
		return s << "Times New Roman";
	}
}

class Paragraph {
public:
	static Paragraph* getParagraph(std::string stil);
	static void registerNewParagraphStyle(std::string style, Paragraph* p);
	void setFontStyle(FontStyle fontStyle) { this->fontStyle = fontStyle; }
	void setFontSize(unsigned int fontSize) { this->fontSize = fontSize; }
	void setAlignment(Alignment alignment) { this->alignment = alignment; }
	void setText(std::string text) { this->text = text; }
	void setIndentFirstLine(bool indenFirstLine) { this->indentFirstLine = indenFirstLine; }
	virtual Paragraph* clone() {
		return new Paragraph(text, fontStyle, fontSize, alignment, indentFirstLine);
	}
	friend std::ostream& operator << (std::ostream& s, const Paragraph& p) {
		s << p.text << "\tconfig: ";
		s << "{fontSize: " << p.fontSize << ", fontStyle: " << p.fontStyle << ", alignment: " \
			<< p.alignment << ", firstLineIndented: " << p.indentFirstLine << "}";
		return s;
	}
	Paragraph(
		std::string text, 
		FontStyle fontStyle, 
		unsigned fontSize,
		Alignment alignment,
		bool indentFirstLine
		) :
			text(text), fontSize(fontSize), 
			fontStyle(fontStyle), alignment(alignment),
			indentFirstLine(indentFirstLine) {}

public:
	std::string text;
private:
	static std::unordered_map<std::string, Paragraph*> styles;

	FontStyle fontStyle;
	Alignment alignment;
	unsigned int fontSize;
	bool indentFirstLine;
};

std::unordered_map<std::string, Paragraph*> Paragraph::styles = 
	std::unordered_map<std::string, Paragraph*>();

void Paragraph::registerNewParagraphStyle(std::string style, Paragraph* p) {
	if (styles.find(style) != styles.end()) {
		delete styles[style];
	}
	styles[style] = p->clone();
}

Paragraph* Paragraph::getParagraph(std::string style) {
	return styles[style]->clone();
}

int main() {
	Paragraph* p1 = new Paragraph("text", FontStyle::TIMES_NEW_ROMAN, 12, Alignment::CENTER, false);
	Paragraph::registerNewParagraphStyle("s1", p1);
	// after we register new style, we can create paragraphs using function getParagraph(style)
	Paragraph* p2 = Paragraph::getParagraph("s1");
	// instead manually creating same paragraph, we made it easier to create multiple paragraphs with same 
	// settings without repeating code
	p2->setText("text 2");
	Paragraph* p3 = Paragraph::getParagraph("s1");
	p3->setText("text 3");

	std::cout << *p1 << std::endl;
	std::cout << *p2 << std::endl;
	std::cout << *p3 << std::endl;
}