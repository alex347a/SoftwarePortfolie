#ifndef GROTTEGENERATOR_H
#define GROTTEGENERATOR_H

#include "FjendeFactory.h"
#include "Grotte.h"

#include <vector>

using namespace std;

class GrotteGenerator
{
public:
    GrotteGenerator(FjendeFactory *factory);

    vector<Grotte> genererGrotter(int helteLevel, int antal);

private:
    FjendeFactory *fjendeFactory;

    string lavGrotteNavn();
    int bestemAntalFjender(int helteLevel);
    int beregnGuld(int helteLevel, int antalFjender);
};

#endif