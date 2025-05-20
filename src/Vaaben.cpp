#include "Vaaben.h"

using namespace std;

Vaaben::Vaaben(string navn, int baseStyrke, int skaleringsFaktor, int holdbarhed)
    : navn(navn), baseStyrke(baseStyrke), skaleringsFaktor(skaleringsFaktor), maxHoldbarhed(holdbarhed), nuvaerendeHoldbarhed(holdbarhed) {}

string Vaaben::hentNavn() const {
    return navn;
}

int Vaaben::hentTotalStyrke(int heroBaseStyrke) const {
    return baseStyrke + skaleringsFaktor * heroBaseStyrke;
}

int Vaaben::hentNuvaerendeHoldbarhed() const {
    return nuvaerendeHoldbarhed;
}

int Vaaben::hentMaxHoldbarhed() const {
    return maxHoldbarhed;
}

void Vaaben::brug() {
    if (nuvaerendeHoldbarhed > 0) {
        nuvaerendeHoldbarhed--;
    }
}

bool Vaaben::erOedelagt() const {
    return nuvaerendeHoldbarhed <= 0;
}