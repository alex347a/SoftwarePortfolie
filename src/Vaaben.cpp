#include "Vaaben.h"

using namespace std;

Vaaben::Vaaben(string navn, int baseStyrke, int skaleringsFaktor, int holdbarhed)
    : navn(navn), baseStyrke(baseStyrke), skaleringsFaktor(skaleringsFaktor), maxHoldbarhed(holdbarhed), nuvaerendeHoldbarhed(holdbarhed) {}

string Vaaben::hentNavn() const
{
    return navn;
}

int Vaaben::hentBaseStyrke() const
{
    return baseStyrke;
}

int Vaaben::hentSkaleringsFaktor() const
{
    return skaleringsFaktor;
}

int Vaaben::hentTotalStyrke(int heroBaseStyrke) const
{
    return baseStyrke + skaleringsFaktor * heroBaseStyrke;
}

int Vaaben::hentNuvaerendeHoldbarhed() const
{
    return nuvaerendeHoldbarhed;
}

int Vaaben::hentMaxHoldbarhed() const
{
    return maxHoldbarhed;
}

int Vaaben::setNuvaerendeHoldbarhed(int holdbarhed)
{
    if (holdbarhed < 0)
    {
        nuvaerendeHoldbarhed = 0;
    }
    else if (holdbarhed > maxHoldbarhed)
    {
        nuvaerendeHoldbarhed = maxHoldbarhed;
    }
    else
    {
        nuvaerendeHoldbarhed = holdbarhed;
    }
    return nuvaerendeHoldbarhed;
}

void Vaaben::brug()
{
    if (nuvaerendeHoldbarhed > 0)
    {
        nuvaerendeHoldbarhed--;
    }
}

bool Vaaben::erOedelagt() const
{
    return nuvaerendeHoldbarhed <= 0;
}

int Vaaben::hentVaabenId() const
{
    return vaabenId;
}

void Vaaben::saetVaabenId(int id)
{
    vaabenId = id;
}

int Vaaben::hentVaabenTypeId() const
{
    return vaabenTypeId;
}

void Vaaben::saetVaabenTypeId(int typeId)
{
    vaabenTypeId = typeId;
}