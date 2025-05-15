#include "Hero.h"

Hero::Hero() {}

// Constructor til Hero med custom navn
Hero::Hero(string navn)
    : Karakter(navn, 10, 10, 2), xp(0), level(1), guld(0) {}

// Constructor til predefinerede Heros
Hero::Hero(string navn, int maxHP, int hp, int styrke, int xp, int level, int guld)
    : Karakter(navn, maxHP, hp, styrke), xp(xp), level(level), guld(guld) {}

int Hero::hentLevel() const {
    return level;
}

int Hero::hentXP() const {
    return xp;
}

int Hero::hentGuld() const {
    return guld;
}

void Hero::givFuldHP() {
    hp = maxHP;
}

void Hero::givXP(int xpMængde) {
    xp += xpMængde;
}

void Hero::givGuld(int guldMængde) {
    guld += guldMængde;
}

bool Hero::levelOp() {
    int levelGrænse = level * 1000;
    if (xp >= levelGrænse) {
        xp -= levelGrænse;
        level++;
        maxHP += 2;
        styrke += 1;
        return true;
    }
    return false;
}

Hero::~Hero() {}