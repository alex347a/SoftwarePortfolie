#ifndef KARAKTER_H
#define KARAKTER_H

#include <string>

using namespace std;

class Karakter
{
public:
    Karakter();
    Karakter(string navn, int maxHP, int hp, int styrke);

    string hentNavn() const;
    int hentMaxHP() const;
    int hentHP() const;
    int hentStyrke() const;

    void tagSkade(int maengde);
    bool erILive() const;

    virtual ~Karakter() = default; // Arv

protected:
    string navn;
    int maxHP;
    int hp;
    int styrke;
};

#endif
