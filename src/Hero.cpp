#include "Hero.h"

using namespace std;

Hero::Hero(string navn)
    : navn(navn), level(1), hp(10), xp(0), styrke(2) {}

string Hero::hentNavn() const { return navn; }
int Hero::hentLevel() const { return level; }
int Hero::hentHP() const { return hp; }
int Hero::hentXP() const { return xp; }
int Hero::hentStyrke() const { return styrke; }

void Hero::tagSkade(int mængde) {
    hp -= mængde;
}

void Hero::givXP(int mængde) {
    xp += mængde;
}

bool Hero::levelOp() {
    int levelGrænse = level * 1000;
    if (xp >= levelGrænse) {
        xp -= levelGrænse;
        level++;
        hp += 2;
        styrke += 1;
        return true;
    }
    return false;
}

bool Hero::erILive() const {
    return hp > 0;
}
