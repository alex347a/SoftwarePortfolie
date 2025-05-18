#include "GameManager.h"
#include "StandardFjendeFactory.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

GameManager::GameManager() {
    opretFjender();
    opretPredefineredeHelte();

    aktivHero = nullptr;
    grottegren = nullptr;
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
        
        valg = hentGyldigtTal(1, 3);

        switch (valg) {
            case 1:
                nyHero();
                aktivHero->tilføjVåben(Våben("Jernsværd", 5, 1, 20));
                aktivHero->tilføjVåben(Våben("Hammer", 3, 2, 30));
                aktivHero->tilføjVåben(Våben("Ståløkse", 8, 3, 15));
                eventyrMenu();
                break;
            case 2:
                loadHero();
                aktivHero->tilføjVåben(Våben("Jernsværd", 5, 1, 20));
                aktivHero->tilføjVåben(Våben("Hammer", 3, 2, 30));
                aktivHero->tilføjVåben(Våben("Ståløkse", 8, 3, 15));
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

// Jeg burde flytte en funktion som denne til en separat fil kaldt utility el.
bool GameManager::erKunWhitespaces(const string& tekst) {
    for (char c : tekst) {
        if (!isspace(c)) {
            return false;
        }
    }
    return true;
}


void GameManager::nyHero() {
    string navn;
    bool gyldigtNavn = false;

    while (!gyldigtNavn) {
        cout << "Indtast navn på ny helt: ";
        getline(cin, navn);

        if (erKunWhitespaces(navn)) {
            cout << "Navn må ikke være tomt eller kun bestå af mellemrum.\n";
            continue;
        }

        bool eksistererAllerede = false;
        for (size_t i = 0; i < predefineredeHelte.size(); ++i) {
        const Hero& h = predefineredeHelte[i];
        if (navn == h.hentNavn()) {
                eksistererAllerede = true;
                break;
            }
        }

        if (eksistererAllerede) {
            cout << "Navnet findes allerede. Prøv et andet.\n";
        } else {
            gyldigtNavn = true;
        }
    }


    aktivHero = new Hero(navn);
    cout << "Ny helt oprettet: " << aktivHero->hentNavn() << endl;
}


void GameManager::loadHero() {
    cout << "--- Vælg en eksisterende helt ---\n";
    for (size_t i = 0; i < predefineredeHelte.size(); ++i) {
        cout << i + 1 << ". " << predefineredeHelte[i].hentNavn() 
        << " HP: " << predefineredeHelte[i].hentMaxHP() 
        << ", Styrke: " << predefineredeHelte[i].hentStyrke() 
        << ", Level: " << predefineredeHelte[i].hentLevel()
        << ", Guld: " << predefineredeHelte[i].hentGuld()
        << endl;
    }

    cout << "Valg: ";
    int valg = hentGyldigtTal(1, predefineredeHelte.size());

    aktivHero = new Hero(predefineredeHelte[valg - 1]);
    cout << "Helt valgt: " << aktivHero->hentNavn() << endl;
}

void GameManager::opretGrotter() {
    if (!aktivHero) {
        cout << "Kan ikke oprette grotter uden en aktiv helt.\n";
        return;
    }

    if (!grottegren) {
        grottegren = new GrotteGenerator(new StandardFjendeFactory(fjendeListe));
    }
    grotterne = grottegren->genererGrotter(aktivHero->hentLevel(), aktivHero->hentLevel());
}


bool GameManager::eventyrMenu() {
    int valg;

    do {
        cout << "\n--- EVENTYR MENU ---\n";
        cout << "1. Kæmp mod en fjende\n";
        cout << "2. Udforsk en grotte\n";
        cout << "3. Vis inventar\n";
        cout << "4. Tilbage til hovedmenu\n";
        cout << "Valg: ";
        
        valg = hentGyldigtTal(1, 4);

        switch (valg) {
            case 1:
                kæmpModFjende();
                if (!aktivHero->erILive()) {
                    return true;
                }
                break;
            case 2:
                opretGrotter();
                if (vælgOgGennemførGrotte()) {
                    return true;
                }
                break;
            case 3:
                visInventarMenu(); 
                break;
                if (!aktivHero->erILive()) {
                    return true;
                }
            case 4:
                cout << "Tilbage til hovedmenu...\n";
                return true;
            default:
                cout << "Ugyldigt valg. Prøv igen.\n";
        }

    } while (valg != 4 && aktivHero->erILive());
    return true;
}

// Hjælpefunktion til at sørge for gyldigt input af brugeren
// Jeg burde flytte en funktion som denne til en separat fil kaldt utility el.
int GameManager::hentGyldigtTal(int min, int max) {
    int valg;
    string input;

    while (true) {
        getline(cin, input);
        stringstream ss(input);

        if (ss >> valg && !(ss >> input)) { // sikrer hele input er et heltal
            if (valg >= min && valg <= max) {
                return valg;
            }
        }

        cout << "Indtast venligst et tal mellem " << min << " og " << max << ": ";
    }
}

void GameManager::kæmpModFjende() {
    Fjende fjende = vælgFjende();
    cout << "--- KAMP ---\n";
    cout << aktivHero->hentNavn() << " kæmper mod " << fjende.hentNavn() << "!\n\n";
    
    cout << aktivHero->hentNavn() << " har\n" 
    << "HP: " << aktivHero->hentHP() << "\n"
    << "styrke: "<<aktivHero->hentStyrke() << "\n\n";

    cout << fjende.hentNavn() << " har\n" 
    << "HP: " << fjende.hentHP() << "\n";

    if (aktivHero->hentUdstyretVåben()) {
        cout << "Våben: " << aktivHero->hentUdstyretVåben()->hentNavn() << " (" << aktivHero->hentUdstyretVåben()->hentNuværendeHoldarhed() << "/" << aktivHero->hentUdstyretVåben()->hentMaxHoldbarhed() << ")\n"
        << "Skade:" << aktivHero->hentSkadeMedVåben() << "\n\n";
        aktivHero->brugAktivVåben();
    } else {
        cout << "styrke: "<< fjende.hentStyrke() << "\n\n";
    }
    
    while (aktivHero->erILive() && fjende.erILive()) {
        cout << "Tryk på ENTER for at angribe!\n";

        string input;
        getline(cin, input);
        if (input.empty()) {
            cout << aktivHero->hentNavn() << " rammer " << fjende.hentNavn() << " for ";
            if (aktivHero->hentUdstyretVåben()) {
                cout << aktivHero->hentSkadeMedVåben() << " skade!\n";
                fjende.tagSkade(aktivHero->hentSkadeMedVåben());
            } else {
                cout << aktivHero->hentStyrke() << " skade!\n";
                fjende.tagSkade(aktivHero->hentStyrke());
            }
        } else {
            cout << aktivHero->hentNavn() << " fumler og rammer ikke!\n";
        }

        if (fjende.hentNavn() == "Dragon" && !fjende.erILive()) {
            cout << "Du besejrede dragen! Du har vundet spillet!\n";
            cout << "Tillykke, " << aktivHero->hentNavn() << "!\n";
            cout << "Forlader spillet...\n";
            exit(0);
        }

        if (!fjende.erILive()) {
            break;
        }

        cout << fjende.hentNavn() << " har " << fjende.hentHP() << " HP tilbage.\n\n";
        cout << fjende.hentNavn() << " rammer " << aktivHero->hentNavn() << " for " << fjende.hentStyrke() << " skade!\n";

        aktivHero->tagSkade(fjende.hentStyrke());

        if (!aktivHero->erILive()) {
            break;
        }

        cout << aktivHero->hentNavn() << " har " << aktivHero->hentHP() << " HP tilbage.\n\n";
        
    }

    if (aktivHero->erILive()) {
        aktivHero->givFuldHP();
        // Murloc får double XP
        if (aktivHero->hentNavn() == "Murloc") {
            cout << aktivHero->hentNavn() << " vandt og får double XP! " << aktivHero->hentNavn() << " får derfor " << fjende.hentXPGevinst()*2 << " XP!\n";
            aktivHero->givXP(fjende.hentXPGevinst()*2);
        } else {
            cout << aktivHero->hentNavn() << " vandt og får " << fjende.hentXPGevinst() << " XP!\n";
            aktivHero->givXP(fjende.hentXPGevinst());
        }
        
        while (aktivHero->levelOp()) {
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

// Denne funktion er næsten identisk med kæmpModFjende, men den tager en fjende som parameter
// og kæmper mod den i stedet for at vælge en fra listen.
void GameManager::kæmpModFjendeIGrotte(const Fjende& fjende) {
    Fjende kopi = fjende;

    cout << "--- GROTTEKAMP ---\n";
    cout << aktivHero->hentNavn() << " kæmper mod " << kopi.hentNavn() << "!\n\n";
    
    cout << aktivHero->hentNavn() << " har\n" 
    << "HP: " << aktivHero->hentHP() << "\n";
    
    if (aktivHero->hentUdstyretVåben()) {
        cout << "Våben: " << aktivHero->hentUdstyretVåben()->hentNavn() << " (" << aktivHero->hentUdstyretVåben()->hentNuværendeHoldarhed() << "/" << aktivHero->hentUdstyretVåben()->hentMaxHoldbarhed() << ")\n"
        << "Skade:" << aktivHero->hentSkadeMedVåben() << "\n\n";
        aktivHero->brugAktivVåben();
    } else {
        cout << "styrke: "<< fjende.hentStyrke() << "\n\n";
    }

    cout << kopi.hentNavn() << " har\n" 
    << "HP: " << kopi.hentHP() << "\n"
    << "styrke: "<< kopi.hentStyrke() << "\n\n";
    
    while (aktivHero->erILive() && kopi.erILive()) {
        cout << "Tryk på ENTER for at angribe!\n";

        string input;
        getline(cin, input);
        if (input.empty()) {
            cout << aktivHero->hentNavn() << " rammer " << kopi.hentNavn() << " for ";
            if (aktivHero->hentUdstyretVåben()) {
                cout << aktivHero->hentSkadeMedVåben() << " skade!\n";
                kopi.tagSkade(aktivHero->hentSkadeMedVåben());
            } else {
                cout << aktivHero->hentStyrke() << " skade!\n";
                kopi.tagSkade(aktivHero->hentStyrke());
            }
        } else {
            cout << aktivHero->hentNavn() << " fumler og rammer ikke!\n";
        }

        if (!kopi.erILive()) {
            break;
        }

        cout << kopi.hentNavn() << " har " << kopi.hentHP() << " HP tilbage.\n\n";
        cout << kopi.hentNavn() << " rammer " << aktivHero->hentNavn() << " for " << kopi.hentStyrke() << " skade!\n";

        aktivHero->tagSkade(kopi.hentStyrke());

        if (!aktivHero->erILive()) {
            break;
        }

        cout << aktivHero->hentNavn() << " har " << aktivHero->hentHP() << " HP tilbage.\n\n";
        
    }

    if (aktivHero->erILive()) {
        aktivHero->givFuldHP();
        // Murloc får double XP
        if (aktivHero->hentNavn() == "Murloc") {
            cout << aktivHero->hentNavn() << " vandt og får double XP! " << aktivHero->hentNavn() << " får derfor " << fjende.hentXPGevinst()*2 << " XP!\n";
            aktivHero->givXP(kopi.hentXPGevinst()*2);
        } else {
            cout << aktivHero->hentNavn() << " vandt og får " << kopi.hentXPGevinst() << " XP!\n";
            aktivHero->givXP(kopi.hentXPGevinst());
        }
        
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
    for (size_t i = 0; i < fjendeListe.size(); ++i) {
        cout << i + 1 << ". " << fjendeListe[i].hentNavn() << " (HP: "
             << fjendeListe[i].hentMaxHP() << ", Styrke: "
             << fjendeListe[i].hentStyrke() << ")\n";
    }
}

Fjende GameManager::vælgFjende() {
    cout << "--- Vælg en fjende ---\n";
    visFjender();
    int valg;
    valg = hentGyldigtTal(1, fjendeListe.size());
    return fjendeListe[valg - 1];
}

void GameManager::opretFjender() {
    fjendeListe.push_back(Fjende("Wolf Cub", 4, 4, 1, 100));
    fjendeListe.push_back(Fjende("Young Forest Wolf", 4, 4, 2, 200));
    fjendeListe.push_back(Fjende("Feronius the Ferocious", 8, 8, 3, 400));
    fjendeListe.push_back(Fjende("Beach Crawler", 10, 10, 4, 500));
    fjendeListe.push_back(Fjende("Young Crocolisk", 15, 15, 5, 800));
    fjendeListe.push_back(Fjende("Mother Crocolisk", 30, 30, 5, 1000));
    fjendeListe.push_back(Fjende("Kobold Miner", 15, 15, 10, 1500));
    fjendeListe.push_back(Fjende("Fagnus the Mage", 13, 13, 20, 2000));
    fjendeListe.push_back(Fjende("Dragon", 100, 100, 10, 3000));
}

bool GameManager::vælgOgGennemførGrotte() {
    cout << "--- Vælg en grotte ---\n";
    for (size_t i = 0; i < grotterne.size(); ++i) {
        cout << i + 1 << ": " << grotterne[i].hentNavn() << " (Guld: " << grotterne[i].hentGuld() << ")\n";

    cout << "   Fjender: ";
        const vector<Fjende>& fjender = grotterne[i].hentFjender();
        for (size_t j = 0; j < fjender.size(); ++j) {
            cout << fjender[j].hentNavn();
            if (j != fjender.size() - 1) {
                cout << ",\n            ";
            }
        }
        cout << endl << endl;
    }

    int valg = hentGyldigtTal(1, grotterne.size());
    Grotte valgt = grotterne[valg - 1];

    for (Fjende fjende : valgt.hentFjender()) {
        cout << "Du møder: " << fjende.hentNavn() << "\n";
        kæmpModFjendeIGrotte(fjende);
        if (!aktivHero->erILive()) {
            cout << "Du er død og kan ikke fortsætte eventyret.\n";
            return true;
        }
    }

    aktivHero->givGuld(valgt.hentGuld());
    cout << "Du har gennemført " << valgt.hentNavn() << " og får " << valgt.hentGuld() << " guld!\n";
    cout << "Du har nu " << aktivHero->hentGuld() << " guld.\n"; 

    // Rydder alle grotter sådan at der dannes nye grotter næste gang
    grotterne.clear();
    
    return false;
}

void GameManager::visInventarMenu() {
    int valg;
    if (!aktivHero) {
        cout << "Ingen aktiv helt!\n";
        return;
    }
    else if (aktivHero->hentAntalVåben() == 0) {
        cout << "Ingen våben i inventar!\n";
        return;
    } 
    do {
        aktivHero->visInventar();
        cout << "\n1. Udstyr våben\n"
             << "2. Tilbage til eventyrmenu\n"
             << "Valg: ";

        valg = hentGyldigtTal(1, 2);

        if (valg == 1) {
            cout << "Vælg våben (1-" << aktivHero->hentAntalVåben() << "): ";
            int valgAfVåben = hentGyldigtTal(1, aktivHero->hentAntalVåben());

            if (aktivHero->udstyrMedVåbenFraIndex(valgAfVåben - 1)) {
                cout << "Du har nu udstyret " 
                     << aktivHero->hentUdstyretVåben()->hentNavn() << "!\n";
            } else {
                cout << "Kunne ikke udstyre våben!\n";
            }
        }
    } while (valg != 2);
}


void GameManager::opretPredefineredeHelte() {
    predefineredeHelte.push_back(Hero("Murloc", 4, 4, 1, 0, 1, 0));
    predefineredeHelte.push_back(Hero("Thor", 14, 14, 4, 0, 4, 0));
    predefineredeHelte.push_back(Hero("Loke", 8, 8, 6, 0, 3, 0));
    predefineredeHelte.push_back(Hero("Odin", 18, 18, 3, 0, 5, 0));
}

GameManager::~GameManager() {
    delete aktivHero;
    delete grottegren;
}
