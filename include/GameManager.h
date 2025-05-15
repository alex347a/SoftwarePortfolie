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
    void eventyrMenu();

    int hentGyldigtTal(int min, int max);
    bool erKunWhitespaces(const string& tekst);

    void kæmpModFjende();
    void kæmpModFjendeIGrotte(const Fjende& fjende);
    void visFjender() const;
    Fjende vælgFjende();
    void opretGrotter();
    void vælgOgGennemførGrotte();

    vector<Fjende> fjendeListe;
    vector<Hero> predefineredeHelte;

    vector<Grotte> grotterne;
    GrotteGenerator* grottegren;
    
    Hero* aktivHero;

    void opretFjender();
    void opretPredefineredeHelte();
};

#endif
