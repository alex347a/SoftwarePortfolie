#include "Hero.h"

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

int Hero::hentEffektivSkade() const {
    if (aktivVåben) {
        return aktivVåben->hentTotalStyrke(styrke);
    }
    return styrke;
}

int Hero::hentAntalVåben() const {
    return inventar.size();
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

void Hero::tilføjVåben(Våben våben) {
    inventar.push_back(våben);
}

void Hero::setAktivVåben(Våben* våben) {
    aktivVåben = våben;
}

void Hero::visInventar() const {
    if (inventar.empty()) {
        cout << "No weapons in inventory!\n";
        return;
    }

    cout << "=== Weapons Inventory ===\n";
    for (size_t i = 0; i < inventar.size(); ++i) {
        cout << i + 1 << ". " << inventar[i].hentNavn()
                  << " (Dmg: +" << inventar[i].hentTotalStyrke(styrke)
                  << ", Dur: " << inventar[i].hentNuværendeHoldarhed()
                  << "/" << inventar[i].hentMaxHoldbarhed() << ")";
        
        if (aktivVåben == &inventar[i]) {
            cout << " [EQUIPPED]";
        }
        cout << "\n";
    }
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

bool Hero::udstyrMedVåbenFraIndex(int index) {
    if (index < 0 || index >= inventar.size()) {
        cout << "Invalid weapon index!\n";
        return false;
    }
    aktivVåben = &inventar[index];
    return true;
}

const Våben* Hero::hentUdstyretVåben() const {
    return aktivVåben;
}