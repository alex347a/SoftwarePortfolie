#ifndef STANDARD_FJENDE_FACTORY_H
#define STANDARD_FJENDE_FACTORY_H

#include "FjendeFactory.h"

#include <string>
#include <vector>

using namespace std;

class StandardFjendeFactory : public FjendeFactory
{
public:
    StandardFjendeFactory(const vector<Fjende> &fjender);

    Fjende skabFjende(int helteLevel) override;
    vector<Fjende> skabFjender(int helteLevel, int antal) override;

    ~StandardFjendeFactory();

private:
    Fjende lavFjendeMedModifier(const string &fjendeNavn, const string &modifier);

    vector<Fjende> fjendeListe;
    vector<string> fjendeNavn;
    vector<string> styrkeModifiers;
};

#endif
