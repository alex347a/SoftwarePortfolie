#ifndef GROTTE_H
#define GROTTE_H

#include <string>
#include <vector>
#include "Fjende.h"

using namespace std;

class Grotte {
public:
    Grotte();
    Grotte(string navn, int guld, vector<Fjende> fjender);

    const string& hentNavn() const;
    int hentGuld() const;
    const vector<Fjende>& hentFjender() const;

    ~Grotte();

protected:
    string navn;
    int guld;
    vector<Fjende> fjender;
};

#endif
