#ifndef HERO_H
#define HERO_H

#include "Karakter.h"

using namespace std;

class Hero : public Karakter {
private:
    int xp;
    int level;

public:
    Hero(string navn);

    int hentLevel() const;
    int hentXP() const;

    void givXP(int mængde);
    bool levelOp();
};

#endif
