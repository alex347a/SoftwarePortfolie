#ifndef HERO_H
#define HERO_H

#include "Karakter.h"
#include "Våben.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Hero : public Karakter {
public:
    Hero(string navn);
    Hero(string navn, int maxHP, int hp, int styrke, int xp, int level, int guld);

    int hentLevel() const;
    int hentXP() const;
    int hentGuld() const;
    int hentSkadeMedVåben() const;
    int hentAntalVåben() const;

    void givFuldHP();
    void givXP(int xpMængde);
    void givGuld(int guldMængde);
    void tilføjVåben(Våben våben);
    void setAktivVåben(Våben* våben);
    void visInventar() const;
    void brugAktivVåben();

    bool levelOp();
    bool udstyrMedVåbenFraIndex(int index);

    const Våben* hentUdstyretVåben() const;
    
private:
    int xp;
    int level;
    int guld;
    vector<Våben> inventar;
    Våben* aktivVåben;
};

#endif
