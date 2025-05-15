#ifndef HERO_H
#define HERO_H

#include "Karakter.h"

using namespace std;

class Hero : public Karakter {
public:
    Hero();
    Hero(string navn);
    Hero(string navn, int maxHP, int hp, int styrke, int xp, int level, int guld);

    int hentLevel() const;
    int hentXP() const;
    int hentGuld() const;

    void givFuldHP();
    void givXP(int xpMængde);
    void givGuld(int guldMængde);

    bool levelOp();

    ~Hero();

protected:
    int xp;
    int level;
    int guld;
};

#endif
