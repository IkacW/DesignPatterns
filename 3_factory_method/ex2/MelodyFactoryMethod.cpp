#include <iostream>

using namespace std;

enum class Genre { ROCK, BALLAD, POP};

/* abstract product, it has only one method to demostrate use of product */
class Melody {
public:
    virtual void play() = 0;
};

/* concrete product */
class RockMelody: public Melody {
public:
    void play() {
        cout << "Pogledaj dom svoj andjele..." << endl;
    }
};
/* konkretan proizvod */
class BalladMelody: public Melody {
    void play() {
        cout << "Bila je tako leeeeepa..." << endl;
    }
};
/* konkretan proizvod */
class PopMelody: public Melody {
    void play() {
        cout << "Ispred teatra Baljsoj, ja sam te cekao..." << endl;
    }
};

/* abstract creator which has fabric method getMelody */
class MusicBox {
public:
    virtual Melody* getMelody(Genre genre) = 0;
};
/* concrete cretor which creates desired concrete product based on passed type,
   different solution is to have for each concrete product one concrete creator */
class CountryMusicBox: public MusicBox {
public:
    Melody* getMelody(Genre genre) {
        switch (genre) {
        case Genre::ROCK: return new RockMelody();
        case Genre::POP: return new PopMelody();
        case Genre::BALLAD: return new BalladMelody();
        default: return NULL;
        }
    }
};

/* using factory method, we are creating concrete creator (CountryMusicBox) seen as MusicBox
   with his help we are creating concrete product (RockMelody) seen as Melody */
int main() {
    MusicBox *musicBox = new CountryMusicBox();
    Melody *rockMelody = musicBox->getMelody(Genre::ROCK);
    rockMelody->play();

    Melody *popMelody = musicBox->getMelody(Genre::POP);
    popMelody->play();

    cout << "Enter genre of melody that you want me to play(R-Rock, B-Ballad, P-Pop): ";
    char type;
    cin >> type;
    Melody *myMelody;
    switch (toupper(type)) {
    case 'R': myMelody = musicBox->getMelody(Genre::ROCK); break;
    case 'B': myMelody = musicBox->getMelody(Genre::BALLAD); break;
    case 'P': myMelody = musicBox->getMelody(Genre::POP); break;
    default: myMelody = NULL;
    }
    if (myMelody != NULL) {
        myMelody->play();
    } else {
        cout << "Unrecognized type of melody" << endl;
    }

    delete musicBox;
    delete rockMelody;
    delete popMelody;
    delete myMelody;
}
