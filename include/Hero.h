#ifndef HERO_H
#define HERO_H

#include "Karakter.h"
#include "Vaaben.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Hero : public Karakter
{
public:
    Hero(string navn);
    Hero(string navn, int maxHP, int hp, int styrke, int xp, int level, int guld);

    int hentLevel() const;
    int hentXP() const;
    int hentGuld() const;
    int hentStyrke() const;
    int hentSkadeMedVaaben() const;
    int hentAntalVaaben() const;

    void givFuldHP();
    void givXP(int xpMaengde);
    void givGuld(int guldMaengde);
    void tilfoejVaaben(Vaaben Vaaben);
    void setAktivVaaben(Vaaben *Vaaben);
    void visInventar() const;
    void brugAktivVaaben();

    bool levelOp();
    bool udstyrMedVaabenFraIndex(int index);

    const Vaaben *hentUdstyretVaaben() const;

    void setDatabaseId(int id); 
    int getDatabaseId() const;

private:
    int xp;
    int level;
    int guld;
    int id;

    vector<Vaaben> inventar;
    Vaaben *aktivVaaben;
};

#endif
