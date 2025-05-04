#ifndef STANDARD_FJENDE_FACTORY_H
#define STANDARD_FJENDE_FACTORY_H

#include "FjendeFactory.h"

#include <string>
#include <vector>

using namespace std;

class StandardFjendeFactory : public FjendeFactory {
public:
    StandardFjendeFactory();

    Fjende skabFjende(int helteLevel) override;
    vector<Fjende> skabFjender(int helteLevel, int antal) override;

    ~StandardFjendeFactory();

private:
    Fjende lavFjendeMedModifier(const string& baseNavn, const string& modifier, int helteLevel);
    
    vector<string> baseNavne;
    vector<string> styrkeModifiers;
};

#endif
