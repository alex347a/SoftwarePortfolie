#ifndef VAABEN_H
#define VAABEN_H

#include <string>

using namespace std;

class Vaaben
{
public:
    Vaaben(string navn, int baseStyrke, int skaleringsFaktor, int holdbarhed);

    string hentNavn() const;
    int hentBaseStyrke() const;
    int hentSkaleringsFaktor() const;
    int hentTotalStyrke(int heroBaseStyrke) const;
    int hentNuvaerendeHoldbarhed() const;
    int hentMaxHoldbarhed() const;
    int hentAntalVaaben() const;

    int setNuvaerendeHoldbarhed(int holdbarhed);

    void brug();
    bool erOedelagt() const;

    int hentVaabenId() const;
    int hentVaabenTypeId() const;
    void saetVaabenId(int id);
    void saetVaabenTypeId(int typeId);

private:
    string navn;
    int baseStyrke;
    int skaleringsFaktor;
    int maxHoldbarhed;
    int nuvaerendeHoldbarhed;
    int vaabenId;
    int vaabenTypeId;
};

#endif
