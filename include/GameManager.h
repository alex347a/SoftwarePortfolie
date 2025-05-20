#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Hero.h"
#include "Fjende.h"
#include "Grotte.h"
#include "GrotteGenerator.h"

#include <vector>
#include <memory>

using namespace std;

class GameManager {
public:
    GameManager();
    void start();
    ~GameManager();

protected:
    void visHovedmenu();
    void nyHero();
    void loadHero();
    bool eventyrMenu();
    void visInventarMenu();

    void kaempModFjende();
    void kaempModFjendeIGrotte(const Fjende& fjende);
    void visFjender() const;
    Fjende vaelgFjende();
    void opretGrotter();
    bool vaelgOgGennemfoerGrotte();

    vector<Fjende> fjendeListe;
    vector<Hero> predefineredeHelte;

    vector<Grotte> grotterne;
    GrotteGenerator* grottegren;
    
    Hero* aktivHero;

    void opretFjender();
    void opretPredefineredeHelte();
};

#endif
