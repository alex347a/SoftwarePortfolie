#ifndef HELTREPOSITORY_H
#define HELTREPOSITORY_H

#include "DatabaseManager.h"
#include "Hero.h"

#include <vector>

using namespace std;

class HeltRepository
{
public:
    HeltRepository(DatabaseManager &dbManager);

    bool gemHelt(const Hero &helt);
    bool indlaesHelte(vector<Hero> &helte);
    bool gemHeltVaaben(int heltId, const Vaaben& vaaben);
    vector<Vaaben> indlaesHeltVaaben(int heltId);

private:
    DatabaseManager &dbManager;
};

#endif