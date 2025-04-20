#include "Hero.h"

Hero::Hero(string navn)
    : Karakter(navn, 10, 2), xp(0), level(1) {}

int Hero::hentLevel() const {
    return level;
}

int Hero::hentXP() const {
    return xp;
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
