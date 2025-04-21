#include "GameManager.h"
#include <iostream>

using namespace std;

GameManager::GameManager() {
    opretFjender();
    opretPredefineredeHelte();

    aktivHero = nullptr;
}

void GameManager::start() {
    visHovedmenu();
}

void GameManager::visHovedmenu() {
    int valg;

    do {
        cout << "\n--- HOVEDMENU ---\n";
        cout << "1. Opret ny helt\n";
        cout << "2. Vælg eksisterende helt\n";
        cout << "3. Afslut\n";
        cout << "Valg: ";
        cin >> valg;

        switch (valg) {
            case 1:
                nyHero();
                eventyrMenu();
                break;
            case 2:
                loadHero();
                eventyrMenu();
                break;
            case 3:
                cout << "Spillet afsluttes...\n";
                break;
            default:
                cout << "Ugyldigt valg. Prøv igen.\n";
        }

    } while (valg != 3);
}

void GameManager::nyHero() {
    string navn;
    cout << "Indtast navn på ny helt: ";
    cin >> navn;
    if (navn.empty() || navn == " " || navn == "\n" || navn == predefineredeHelte[0].hentNavn() || navn == predefineredeHelte[1].hentNavn() || navn == predefineredeHelte[2].hentNavn()) {
        cout << "Navn må hverken være tomt eller allerede eksisterende. Vender tilbage til hovedmenu.\n";
        return;
    }
    aktivHero = new Hero(navn);
    cout << "Ny helt oprettet: " << aktivHero->hentNavn() << endl;
}

void GameManager::loadHero() {
    cout << "--- Vælg en eksisterende helt ---\n";
    for (size_t i = 0; i < predefineredeHelte.size(); ++i) {
        cout << i + 1 << ". " << predefineredeHelte[i].hentNavn() << endl;
    }

    int valg;
    cin >> valg;
    if (valg >= 1 && valg <= (int)predefineredeHelte.size()) {
        aktivHero = new Hero(predefineredeHelte[valg - 1]);
        cout << "Helt valgt: " << aktivHero->hentNavn() << endl;
    } else {
        cout << "Ugyldigt valg. Går tilbage til hovedmenu.\n";
    }
}

void GameManager::eventyrMenu() {
    int valg;

    do {
        cout << "\n--- EVENTYR MENU ---\n";
        cout << "1. Kæmp mod en fjende\n";
        cout << "2. Tilbage til hovedmenu\n";
        cout << "Valg: ";
        cin >> valg;

        switch (valg) {
            case 1:
                kæmpModFjende();
                break;
            case 2:
                cout << "Tilbage til hovedmenu...\n";
                break;
            default:
                cout << "Ugyldigt valg. Prøv igen.\n";
        }

    } while (valg != 2 && aktivHero->erILive());
}

void GameManager::kæmpModFjende() {
    Fjende fjende = vælgFjende();
    cout << "--- KAMP ---\n";
    cout << aktivHero->hentNavn() << " kæmper mod " << fjende.hentNavn() << "!\n";

    while (aktivHero->erILive() && fjende.erILive()) {
        cout << aktivHero->hentNavn() << " rammer " << fjende.hentNavn() << " for " << aktivHero->hentStyrke() << " skade!\n";
        fjende.tagSkade(aktivHero->hentStyrke());

        if (!fjende.erILive()) {
            break;
        }

        cout << fjende.hentNavn() << " har " << fjende.hentHP() << " HP tilbage.\n";
        cout << fjende.hentNavn() << " rammer " << aktivHero->hentNavn() << " for " << fjende.hentStyrke() << " skade!\n";

        aktivHero->tagSkade(fjende.hentStyrke());

        if (!aktivHero->erILive()) {
            break;
        }

        cout << aktivHero->hentNavn() << " har " << aktivHero->hentHP() << " HP tilbage.\n";
        
    }

    if (aktivHero->erILive()) {
        aktivHero->givFuldHP();
        cout << aktivHero->hentNavn() << " vandt og får " << fjende.hentXPGevinst() << " XP!\n";
        aktivHero->givXP(fjende.hentXPGevinst());
        if (aktivHero->levelOp()) {
            aktivHero->givFuldHP();
            cout << "Du er steget i level!\n";
            cout << "Nyt level: " << aktivHero->hentLevel() << "\n";
            cout << "Nyt max HP: " << aktivHero->hentMaxHP() << "\n";
            cout << "Nyt styrke: " << aktivHero->hentStyrke() << "\n";
            
        }
        cout << "Du har nu " << aktivHero->hentXP() << " XP.\n";

    } else {
        cout << aktivHero->hentNavn() << " døde i kampen...\n";
    }
}

void GameManager::visFjender() const {
    for (size_t i = 0; i < fjendeliste.size(); ++i) {
        cout << i + 1 << ". " << fjendeliste[i].hentNavn() << " (HP: "
             << fjendeliste[i].hentMaxHP() << ", Styrke: "
             << fjendeliste[i].hentStyrke() << ")\n";
    }
}

Fjende GameManager::vælgFjende() {
    cout << "--- Vælg en fjende ---\n";
    visFjender();
    int valg;
    cin >> valg;
    if (valg >= 1 && valg <= (int)fjendeliste.size()) {
        return fjendeliste[valg - 1];
    } else {
        cout << "Ugyldigt valg. Prøv igen.\n";
        return vælgFjende();
    }
}

void GameManager::opretFjender() {
    fjendeliste.push_back(Fjende("Wolf Cub", 4, 4, 1, 100));
    fjendeliste.push_back(Fjende("Young Forest Wolf", 4, 4, 2, 200));
    fjendeliste.push_back(Fjende("Feronius the Ferocious", 8, 8, 3, 400));
    fjendeliste.push_back(Fjende("Beach Crawler", 10, 10, 4, 500));
    fjendeliste.push_back(Fjende("Young Crocolisk", 15, 15, 5, 800));
    fjendeliste.push_back(Fjende("Mother Crocolisk", 30, 30, 5, 1000));
    fjendeliste.push_back(Fjende("Kobold Miner", 15, 15, 10, 1500));
    fjendeliste.push_back(Fjende("Fagnus the Mage", 11, 11, 20, 2000));
    fjendeliste.push_back(Fjende("Dragon", 100, 100, 10, 3000));
}

void GameManager::opretPredefineredeHelte() {
    predefineredeHelte.push_back(Hero("Thor"));
    predefineredeHelte.push_back(Hero("Loke"));
    predefineredeHelte.push_back(Hero("Odin"));
}

GameManager::~GameManager() {
    delete aktivHero;
}
