#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Hero.h"
#include "Fjende.h"

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
    void visFjender() const;
    Fjende vælgFjende();

    vector<Fjende> fjendeliste;
    vector<Hero> predefineredeHelte;
    
    Hero* aktivHero;

    void opretFjender();
    void opretPredefineredeHelte();
};

#endif
