#include "Fjende.h"

using namespace std;

Fjende::Fjende(string navn, int hp, int styrke, int xpGevinst)
    : Karakter(navn, hp, styrke), xpGevinst(xpGevinst) {}

int Fjende::hentXPGevinst() const {
    return xpGevinst;
}
