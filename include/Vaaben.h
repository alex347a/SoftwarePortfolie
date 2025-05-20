#ifndef VAABEN_H
#define VAABEN_H

#include <string>

using namespace std;

class Vaaben {
public:
    Vaaben(string navn, int baseStyrke, int skaleringsFaktor, int holdbarhed);
    
    string hentNavn() const;
    int hentTotalStyrke(int heroBaseStyrke) const;
    int hentNuvaerendeHoldbarhed() const;
    int hentMaxHoldbarhed() const;
    int hentAntalVaaben() const;

    void brug();
    bool erOedelagt() const;
    
private:
    string navn;
    int baseStyrke;
    int skaleringsFaktor;
    int maxHoldbarhed;
    int nuvaerendeHoldbarhed;
};

#endif
