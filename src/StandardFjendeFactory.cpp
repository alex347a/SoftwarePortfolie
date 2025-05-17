#include "StandardFjendeFactory.h"

StandardFjendeFactory::StandardFjendeFactory(const vector<Fjende>& fjender) 
    : fjendeListe(fjender) {}

Fjende StandardFjendeFactory::skabFjende(int helteLevel) {
    string modifier;
    vector<string> passendeNavne;

    // Vælg en passende modifier baseret på helteLevel
    if (helteLevel <= 2) {
        modifier = "Weak";
    } else if (helteLevel <= 5) {
        modifier = "Average";
    } else if (helteLevel <= 10) {
        modifier = "Strong";
    } else {
        modifier = "Elite";
    }

    int minXP = helteLevel * 100;
    int maxXP = helteLevel * 300;

    // Find passende fjende navne baseret på helteLevel
    for (const Fjende& f : fjendeListe) {
        if (f.hentXPGevinst() >= minXP && f.hentXPGevinst() <= maxXP) {
            passendeNavne.push_back(f.hentNavn());
        }
    }
    return lavFjendeMedModifier(passendeNavne[rand() % passendeNavne.size()], modifier);
}

vector<Fjende> StandardFjendeFactory::skabFjender(int helteLevel, int antal) {
    vector<Fjende> fjender;
    for (int i = 0; i < antal; ++i) {
        fjender.push_back(skabFjende(helteLevel));
    }
    return fjender;
}

Fjende StandardFjendeFactory::lavFjendeMedModifier(const string& fjendeNavn, const string& modifier) {
    string fjendeNavnMedModifier = modifier + " " + fjendeNavn;

    int maxHP;
    int hp = maxHP;
    int styrke;
    int xp;

    // Loop igennem fjendeListe for at finde den rigtige fjende
    for (const Fjende& f : fjendeListe) {
        if (f.hentNavn() == fjendeNavn) {
            maxHP = f.hentMaxHP();
            styrke = f.hentStyrke();
            xp = f.hentXPGevinst();

            if (modifier == "Weak") {
                maxHP *= 0.75;
                styrke *= 0.75;
            } else if (modifier == "Average") {
                xp *= 1.2;
            } else if (modifier == "Strong") {
                maxHP *= 1.5;
                styrke *= 1.5;
                xp *= 1.8;
            } else if (modifier == "Elite") {
                maxHP *= 2;
                styrke *= 2;
                xp *= 2.5;
            }
            if (styrke < 1) styrke = 1;
            hp = maxHP;
            break;
        }
    }

    return Fjende(fjendeNavnMedModifier, maxHP, hp, styrke, xp);
}

StandardFjendeFactory::~StandardFjendeFactory() {}