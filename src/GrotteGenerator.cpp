#include "GrotteGenerator.h"
#include <cstdlib>

GrotteGenerator::GrotteGenerator(FjendeFactory* factory)
    : fjendeFactory(factory) {}

vector<Grotte> GrotteGenerator::genererGrotter(int helteLevel, int antal) {
    vector<Grotte> grotter;

    for (int i = 0; i < antal; ++i) {
        int fjendeAntal = bestemAntalFjender(helteLevel);
        vector<Fjende> fjender = fjendeFactory->skabFjender(helteLevel, fjendeAntal);

        string grotteNavn = lavGrotteNavn();
        int guld = beregnGuld(helteLevel, fjendeAntal);

        grotter.push_back(Grotte(grotteNavn, guld, fjender));
    }

    return grotter;
}

string GrotteGenerator::lavGrotteNavn() {
    string grotteNavn = "Mysterious Cave";
    return grotteNavn;
}

int GrotteGenerator::bestemAntalFjender(int helteLevel) {
    // Antallet af fjender afhaenger af helteLevel
    if (helteLevel <= 2) return rand() % 2 + 1;         // 1–2 fjender
    else if (helteLevel <= 5) return rand() % 3 + 2;    // 2–4 fjender
    else return rand() % 3 + 3;                         // 3–5 fjender
}

// Lav beregningen af guld om. Den skal vaere baseret paa den totale maengde af xp der gives for alle fjenderne i grotten.
int GrotteGenerator::beregnGuld(int helteLevel, int fjendeAntal) {
    return (helteLevel * 10) + (fjendeAntal * 20);
}
