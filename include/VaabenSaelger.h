#ifndef VAABENSAELGER_H
#define VAABENSAELGER_H

#include "Vaaben.h"
#include "Hero.h"

#include <vector>

using namespace std;

class VaabenSaelger {
public:
    VaabenSaelger(const string& saelgerNavn);
    
    int hentAntalVaaben() const;
    void fyldLager(int level);
    void visLager(const Hero& koeber) const;
    int beregnSkade(const Vaaben& vaaben, int heroStyrke) const;
    int beregnPris(const Vaaben& vaaben, int heroStyrke) const;
    bool saelgVaaben(int index, Hero& koeber);

private:
    vector<Vaaben> vaabenLager;
    string saelgerNavn;
};

#endif