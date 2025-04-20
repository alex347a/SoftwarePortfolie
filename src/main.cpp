#include "Hero.h"
#include "Fjende.h"
#include <iostream>

using namespace std;

int main() {
    Hero helt("Alex");
    Fjende fjende("Testfjende", 3, 1, 1001);

    cout << helt.hentNavn() << " kæmper mod " << fjende.hentNavn() << endl;

    while (helt.erILive() && fjende.erILive()) {
        cout << helt.hentNavn() << " ramte " << fjende.hentNavn() << " for " << helt.hentStyrke() << " skade" << endl;
        fjende.tagSkade(helt.hentStyrke());
        if (fjende.erILive()) {
            cout << fjende.hentNavn() << " har " << fjende.hentHP() << " HP tilbage." << endl;
            helt.tagSkade(fjende.hentStyrke());
            cout << fjende.hentNavn() << " ramte " << helt.hentNavn() << " for " << fjende.hentStyrke() << " skade" << endl;
            cout << helt.hentNavn() << " har " << helt.hentHP() << " HP tilbage." << endl;
        }
    }

    if (helt.erILive()) {
        cout << helt.hentNavn() << " vandt og får " << fjende.hentXPGevinst() << " XP" << endl;
        helt.givXP(fjende.hentXPGevinst());
        if (helt.levelOp()) {
            cout << "Du er steget i level!" << endl;
        }
        cout << "Dit nuværende level er: " << helt.hentLevel() << endl;
        cout << "Din nuværende XP er: " << helt.hentXP() << endl;
    } else {
        cout << helt.hentNavn() << " tabte..." << endl;
    }

    return 0;
}

