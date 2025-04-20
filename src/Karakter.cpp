#include "Karakter.h"

using namespace std;

Karakter::Karakter(string navn, int hp, int styrke)
    : navn(navn), hp(hp), styrke(styrke) {}

string Karakter::hentNavn() const { return navn; }
int Karakter::hentHP() const { return hp; }
int Karakter::hentStyrke() const { return styrke; }

void Karakter::tagSkade(int mængde) {
    hp -= mængde;
}

bool Karakter::erILive() const {
    return hp > 0;
}
