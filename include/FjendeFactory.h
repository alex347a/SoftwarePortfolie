#ifndef FJENDEFABRIK_H
#define FJENDEFABRIK_H

#include "Fjende.h"

#include <vector>

using namespace std;

class FjendeFactory {
public:
    FjendeFactory();

    virtual Fjende skabFjende(int helteLevel) = 0;
    virtual vector<Fjende> skabFjender(int helteLevel, int antal) = 0;
    
    virtual ~FjendeFactory() = default;
};
    
#endif