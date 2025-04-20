#ifndef KARAKTER_H
#define KARAKTER_H

#include <string>

using namespace std;

class Karakter {
protected:
    string navn;
    int hp;
    int styrke;

public:
    Karakter(string navn, int hp, int styrke);
    
    string hentNavn() const;
    int hentHP() const;
    int hentStyrke() const;

    void tagSkade(int mængde);
    bool erILive() const;

    virtual ~Karakter() = default; // Arv
};

#endif
