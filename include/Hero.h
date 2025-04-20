#ifndef HERO_H
#define HERO_H

#include <string>

using namespace std;

class Hero {
public:
    Hero();
    Hero(string navn);
    
    string hentNavn() const;
    int hentLevel() const;
    int hentHP() const;
    int hentXP() const;
    int hentStyrke() const;

    void tagSkade(int mængde);
    void givXP(int mængde);
    bool levelOp();
    bool erILive() const;

    ~Hero();
    
protected:
    string navn;
    int level;
    int hp;
    int xp;
    int styrke;
};

#endif
