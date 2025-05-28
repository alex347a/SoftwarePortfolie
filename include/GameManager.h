#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Hero.h"
#include "Fjende.h"
#include "Grotte.h"
#include "GrotteGenerator.h"
#include "VaabenSaelger.h"
#include "DatabaseManager.h"
#include "HeroRepository.h"

#include <vector>
#include <memory>

using namespace std;

class GameManager
{
public:
    GameManager();
    void start();
    ~GameManager();

protected:
    void visHovedmenu();
    void vaelgGemtHero();
    void nyHero();
    void loadHero();
    bool eventyrMenu();
    void visInventarMenu();
    void visVaabenSaelgerMenu();

    void kaempModFjende();
    void kaempModFjendeIGrotte(const Fjende &fjende);
    void visFjender() const;
    Fjende vaelgFjende();
    void opretGrotter();
    bool vaelgOgGennemfoerGrotte();

    vector<Fjende> fjendeListe;
    vector<Hero> predefineredeHeros;
    vector<Hero> gemteHeros;

    vector<Grotte> grotterne;
    GrotteGenerator *grottegren;

    Hero *aktivHero;

    void opretFjender();
    void opretPredefineredeHeros();
    void opretGemteHeros();

    void gemAktivHero();
    void testIndlaesHeros();

    DatabaseManager dbManager;
    HeroRepository heroRepository;
};

#endif