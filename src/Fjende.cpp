#include "Fjende.h"

using namespace std;

Fjende::Fjende(string navn, int maxHP, int hp, int styrke, int xpGevinst)
    : Karakter(navn, maxHP, hp, styrke), xpGevinst(xpGevinst) {}

int Fjende::hentXPGevinst() const {
    return xpGevinst;
}
