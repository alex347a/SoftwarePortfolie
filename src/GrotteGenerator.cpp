#include "GrotteGenerator.h"
#include <cstdlib>

GrotteGenerator::GrotteGenerator(FjendeFactory* factory)
    : fjendeFactory(factory) {}

vector<Grotte> GrotteGenerator::genererGrotter(int helteLevel, int antal) {
    vector<Grotte> grotter;

    for (int i = 0; i < antal; ++i) {
        int fjendeAntal = bestemAntalFjender(helteLevel);
        vector<Fjende> fjender = fjendeFactory->skabFjender(helteLevel, fjendeAntal);

        string navn = lavGrotteNavn(i);
        int guld = beregnGuld(helteLevel, fjendeAntal);

        grotter.push_back(Grotte(navn, guld, fjender));
    }

    return grotter;
}

string GrotteGenerator::lavGrotteNavn(int index) {
    vector<string> navne = {
        "Wolf Den", "Crocolisk Nest", "Ancient Mine", "Dark Forest", "Eye of Sauron"
    };
    return navne[index % navne.size()];
}

int GrotteGenerator::bestemAntalFjender(int helteLevel) {
    // Antallet af fjender afhænger af helteLevel
    if (helteLevel <= 2) return rand() % 2 + 1;         // 1–2 fjender
    else if (helteLevel <= 5) return rand() % 3 + 2;    // 2–4 fjender
    else return rand() % 3 + 3;                         // 3–5 fjender
}

int GrotteGenerator::beregnGuld(int helteLevel, int fjendeAntal) {
    return (helteLevel * 10) + (fjendeAntal * 20);
}
