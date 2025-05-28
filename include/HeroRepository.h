#ifndef HEROREPOSITORY_H
#define HEROREPOSITORY_H

#include "DatabaseManager.h"
#include "Hero.h"

#include <vector>

using namespace std;

class HeroRepository
{
public:
    HeroRepository(DatabaseManager &dbManager);

    bool gemHero(const Hero &hero);
    bool indlaesHeros(vector<Hero> &heros);
    bool gemHeroVaaben(int heroId, const Vaaben& vaaben);
    vector<Vaaben> indlaesHeroVaaben(int heroId);

private:
    DatabaseManager &dbManager;
};

#endif