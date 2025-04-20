#ifndef KARAKTER_H
#define KARAKTER_H

#include <string>

using namespace std;

class Karakter {
public:
    Karakter();
    Karakter(string navn, int hp, int styrke);
    
    string hentNavn() const;
    int hentHP() const;
    int hentStyrke() const;

    void tagSkade(int mængde);
    bool erILive() const;

    virtual ~Karakter() = default; // Arv

protected:
    string navn;
    int hp;
    int styrke;

};

#endif
