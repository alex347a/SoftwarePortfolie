#ifndef HERO_H
#define HERO_H

#include "Karakter.h"

using namespace std;

class Hero : public Karakter {
public:
    Hero();
    Hero(string navn);
    Hero(string navn, int maxHP, int hp, int styrke, int xp, int level);

    int hentLevel() const;
    int hentXP() const;

    void givFuldHP();
    void givXP(int mængde);
    bool levelOp();

    ~Hero();

protected:
    int xp;
    int level;
};

#endif
