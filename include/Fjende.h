#ifndef FJENDE_H
#define FJENDE_H

#include "Karakter.h"

using namespace std;

class Fjende : public Karakter {
public:
    Fjende();
    Fjende(string navn, int maxHP, int hp, int styrke, int xpGevinst);

    int hentXPGevinst() const;

    ~Fjende();

protected:
    int xpGevinst;
};

#endif
