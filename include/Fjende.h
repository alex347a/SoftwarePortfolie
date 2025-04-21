#ifndef FJENDE_H
#define FJENDE_H

#include "Karakter.h"

using namespace std;

class Fjende : public Karakter {
private:
    int xpGevinst;

public:
    Fjende(string navn, int maxHP, int hp, int styrke, int xpGevinst);

    int hentXPGevinst() const;
};

#endif
