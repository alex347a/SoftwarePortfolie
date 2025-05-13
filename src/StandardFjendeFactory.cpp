#include "StandardFjendeFactory.h"

StandardFjendeFactory::StandardFjendeFactory() {
    baseNavne = {"Wolf", "Crawler", "Crocolisk", "Miner", "Mage"};
    styrkeModifiers = {"Weak", "Average", "Strong", "Elite"};
}

Fjende StandardFjendeFactory::skabFjende(int helteLevel) {
    string modifier;
    vector<string> passendeNavne;

    if (helteLevel <= 2) {
        modifier = "Weak";
        passendeNavne = {baseNavne[0], baseNavne[1]};
    }
    else if (helteLevel <= 5) {
        modifier = "Average";
        passendeNavne = {baseNavne[1], baseNavne[2]};
    } else if (helteLevel <= 8) {
        modifier = "Strong";
        passendeNavne = {baseNavne[2], baseNavne[3]};
    } else {
        modifier = "Elite";
        passendeNavne = {baseNavne[3], baseNavne[4]};
    }

    // Vælg tilfældigt fra de passende navne
    string base = passendeNavne[rand() % passendeNavne.size()];
    return lavFjendeMedModifier(base, modifier, helteLevel);
}

vector<Fjende> StandardFjendeFactory::skabFjender(int helteLevel, int antal) {
    vector<Fjende> fjender;
    for (int i = 0; i < antal; ++i) {
        fjender.push_back(skabFjende(helteLevel));
    }
    return fjender;
}

Fjende StandardFjendeFactory::lavFjendeMedModifier(const string& baseNavn, const string& modifier, int helteLevel) {
    string navn = modifier + " " + baseNavn;

    int maxHP = 10 + helteLevel * 2;
    int hp = maxHP;
    int styrke = 3 + helteLevel;
    int xp = 5 + helteLevel;

    if (modifier == "Weak") {
        hp *= 0.8;
        styrke *= 0.8;
        xp *= 1.0;
    } else if (modifier == "Average") {
        hp *= 1.0;
        styrke *= 1.0;
        xp *= 1.2;
    } else if (modifier == "Strong") {
        hp *= 1.2;
        styrke *= 1.2;
        xp *= 1.5;
    } else if (modifier == "Elite") {
        hp *= 1.5;
        styrke *= 1.5;
        xp *= 2;
    }

    return Fjende(navn, maxHP, hp, styrke, xp);
}