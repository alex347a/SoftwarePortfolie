#include "Karakter.h"

using namespace std;

Karakter::Karakter() {}

Karakter::Karakter(string navn, int maxHP, int hp, int styrke)
    : navn(navn), maxHP(maxHP), hp(hp), styrke(styrke) {}

string Karakter::hentNavn() const { return navn; }
int Karakter::hentMaxHP() const { return maxHP; }
int Karakter::hentHP() const { return hp; }
int Karakter::hentStyrke() const { return styrke; }

void Karakter::tagSkade(int maengde)
{
    hp -= maengde;
}

bool Karakter::erILive() const
{
    return hp > 0;
}