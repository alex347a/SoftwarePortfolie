#ifndef ANALYSE_H
#define ANALYSE_H

#include "DatabaseManager.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

class Analyse {
public:
    Analyse(DatabaseManager& dbManager);
    vector<string> hentSorteredeHelteNavne();
    int antalFjenderBesejretAfHero(int heroId);
    // Saa kan jeg bruge map til at gemme en string (vaabenNavn) og int (antal fjender) sammen
    map<string, int> fjenderBesejretPerVaabenForHero(int heroId);
    map<string, string> mestDrabeligeHeroPerVaaben();

private:
    DatabaseManager& dbManager;
};

#endif