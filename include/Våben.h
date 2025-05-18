#ifndef VÅBEN_H
#define VÅBEN_H

#include <string>

using namespace std;

class Våben {
public:
    Våben(string navn, int baseStyrke, int skaleringsFaktor, int holdbarhed);
    
    string hentNavn() const;
    int hentTotalStyrke(int heroBaseStyrke) const;
    int hentNuværendeHoldarhed() const;
    int hentMaxHoldbarhed() const;
    int hentAntalVåben() const;

    void brug();
    bool erØdelagt() const;
    
private:
    string navn;
    int baseStyrke;
    int skaleringsFaktor;
    int maxHoldbarhed;
    int nuværendeHoldbarhed;
};

#endif
