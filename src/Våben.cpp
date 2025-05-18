#include "Våben.h"

using namespace std;

Våben::Våben(string navn, int baseStyrke, int skaleringsFaktor, int holdbarhed)
    : navn(navn), baseStyrke(baseStyrke), skaleringsFaktor(skaleringsFaktor), maxHoldbarhed(holdbarhed), nuværendeHoldbarhed(holdbarhed) {}

string Våben::hentNavn() const {
    return navn;
}

int Våben::hentTotalStyrke(int heroBaseStyrke) const {
    return baseStyrke + skaleringsFaktor * heroBaseStyrke;
}

int Våben::hentNuværendeHoldarhed() const {
    return nuværendeHoldbarhed;
}

int Våben::hentMaxHoldbarhed() const {
    return maxHoldbarhed;
}

void Våben::brug() {
    if (nuværendeHoldbarhed > 0) {
        nuværendeHoldbarhed--;
    }
}

bool Våben::erØdelagt() const {
    return nuværendeHoldbarhed <= 0;
}