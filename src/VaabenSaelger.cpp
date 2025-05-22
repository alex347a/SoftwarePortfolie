#include "VaabenSaelger.h"

VaabenSaelger::VaabenSaelger(const string &saelgerNavn) : saelgerNavn(saelgerNavn)
{
    fyldLager(1);
}

int VaabenSaelger::hentAntalVaaben() const
{
    return vaabenLager.size();
}

void VaabenSaelger::visLager(const Hero &koeber) const
{
    cout << "\n=== " << saelgerNavn << "'s Vaabenudvalg ===\n";
    for (size_t i = 0; i < hentAntalVaaben(); ++i)
    {
        cout << i + 1 << ". " << vaabenLager[i].hentNavn()
             << " (" << vaabenLager[i].hentTotalStyrke(koeber.hentStyrke()) << " skade) - "
             << beregnPris(vaabenLager[i], koeber.hentStyrke()) << " guld\n";
    }
    cout << "0. Afbryd\n";
}

void VaabenSaelger::fyldLager(int level)
{
    vaabenLager.clear();
    vaabenLager.push_back(Vaaben("Jernsvaerd", 5, 1, 20));
    vaabenLager.push_back(Vaaben("Hammer", 3, 2, 30));
    vaabenLager.push_back(Vaaben("Staaloekse", 8, 3, 15));
}

int VaabenSaelger::beregnPris(const Vaaben &vaaben, int heroStyrke) const
{
    return 30 + (vaaben.hentTotalStyrke(heroStyrke) * 10);
}

bool VaabenSaelger::saelgVaaben(int index, Hero &koeber)
{
    if (index < 0 || index >= hentAntalVaaben())
    {
        cout << "Ugyldigt vaabenvalg!\n";
        return false;
    }

    int pris = beregnPris(vaabenLager[index], koeber.hentStyrke());

    if (koeber.hentGuld() >= pris)
    {
        koeber.tilfoejVaaben(vaabenLager[index]);
        koeber.givGuld(-pris);
        cout << "Koebet gennemført: " << vaabenLager[index].hentNavn() << " for " << pris << " guld\n";
        return true;
    }

    cout << "Ikke nok guld! Du har " << koeber.hentGuld() << ", men skal bruge " << pris << "\n";
    return false;
}