#include "GameManager.h"
#include "StandardFjendeFactory.h"
#include "Hjaelpefunktioner.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

GameManager::GameManager() : dbManager("heros.db"), heroRepository(dbManager)
{
    cout << "Initialiserer database...\n";

    const char *skabTabelSQL = "CREATE TABLE IF NOT EXISTS Hero ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "navn TEXT NOT NULL, "
                               "maxHP INTEGER NOT NULL, "
                               "hp INTEGER NOT NULL, "
                               "styrke INTEGER NOT NULL, "
                               "xp INTEGER NOT NULL, "
                               "level INTEGER NOT NULL, "
                               "guld INTEGER NOT NULL)";

    if (!dbManager.eksekverSQLData(skabTabelSQL))
    {
        cerr << "FEJL: Kunne ikke oprette Helt-tabellen. Detaljer:\n";
        cerr << "Databasefil: " << dbManager.hentDB() << "\n"; //
        return;
    }

    // Tjek om tabellen eksisterer
    if (!dbManager.eksekverSQLData("SELECT 1 FROM Hero LIMIT 1"))
    {
        cerr << "FEJL: Helt-tabellen eksisterer ikke eller er tom\n";
    }

    const char *skabVaabenSQL = "CREATE TABLE IF NOT EXISTS Vaaben ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                "vaaben_type_id INTEGER NOT NULL, "
                                "nuvaerendeHoldbarhed INTEGER NOT NULL, "
                                "FOREIGN KEY(vaaben_type_id) REFERENCES VaabenTyper(id))";

    const char *skabVaabenTyperSQL = "CREATE TABLE IF NOT EXISTS VaabenTyper ("
                                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                     "navn TEXT NOT NULL UNIQUE, "
                                     "baseStyrke INTEGER NOT NULL, "
                                     "skaleringsFaktor REAL NOT NULL, "
                                     "maxHoldbarhed INTEGER NOT NULL)";

    const char *skabHeroVaabenSQL = "CREATE TABLE IF NOT EXISTS HeroVaaben ("
                                    "hero_id INTEGER NOT NULL, "
                                    "vaaben_id INTEGER NOT NULL, "
                                    "nuvaerendeHoldbarhed INTEGER NOT NULL, "
                                    "FOREIGN KEY(hero_id) REFERENCES Hero(id), "
                                    "FOREIGN KEY(vaaben_id) REFERENCES Vaaben(id), "
                                    "PRIMARY KEY(hero_id, vaaben_id))";

    dbManager.eksekverSQLData(skabVaabenSQL);
    dbManager.eksekverSQLData(skabVaabenTyperSQL);
    dbManager.eksekverSQLData(skabHeroVaabenSQL);

    opretFjender();
    opretPredefineredeHeros();

    aktivHero = nullptr;
    grottegren = nullptr;
}

void GameManager::start()
{
    visHovedmenu();
}

void GameManager::visHovedmenu()
{
    int valg;

    do
    {
        opretGemteHeros();
        indlaesHeros();
        cout << "\n--- HOVEDMENU ---\n";
        if (gemteHeros.size() != 0)
        {
            cout << "0. Indlaes en tidligere gemt helt\n";
        }
        cout << "1. Opret ny helt\n";
        cout << "2. Vaelg en predefineret helt\n";
        cout << "3. Afslut\n";
        cout << "Valg: ";

        valg = Hjaelpefunktioner::hentGyldigtTal(0, 3);

        switch (valg)
        {
        case 0:
            vaelgGemtHero();
            eventyrMenu();
            break;
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
            cout << "Ugyldigt valg. Proev igen.\n";
        }

    } while (valg != 3);
}

void GameManager::vaelgGemtHero()
{
    cout << "--- Vaelg en gemt helt ---\n";
    for (size_t i = 0; i < gemteHeros.size(); ++i)
    {
        cout << i + 1 << ". " << gemteHeros[i].hentNavn()
             << " HP: " << gemteHeros[i].hentMaxHP()
             << ", Styrke: " << gemteHeros[i].hentStyrke()
             << ", XP: " << gemteHeros[i].hentXP()
             << ", Level: " << gemteHeros[i].hentLevel()
             << ", Guld: " << gemteHeros[i].hentGuld()
             << endl;
    }

    cout << "Valg: ";
    int valg = Hjaelpefunktioner::hentGyldigtTal(1, gemteHeros.size());

    aktivHero = new Hero(gemteHeros[valg - 1]);
    cout << "Helt valgt: " << aktivHero->hentNavn() << endl;
}

void GameManager::nyHero()
{
    string navn;
    bool gyldigtNavn = false;

    while (!gyldigtNavn)
    {
        cout << "Indtast navn paa ny helt: ";
        getline(cin, navn);

        bool eksistererAllerede = false;

        // 1. Tjek om navnet allerede findes i de predefinerede helte
        for (size_t i = 0; i < predefineredeHeros.size(); ++i)
        {
            const Hero &h = predefineredeHeros[i];
            if (navn == h.hentNavn())
            {
                eksistererAllerede = true;
                break;
            }
        }
        // 2. Tjek om navnet allerede findes i de gemte helte
        if (!eksistererAllerede)
        {
            for (const auto &helt : gemteHeros)
            {
                if (navn == helt.hentNavn())
                {
                    eksistererAllerede = true;
                    break;
                }
            }
        }

        if (eksistererAllerede)
        {
            cout << "Navnet findes allerede. Proev et andet.\n";
        }
        else
        {
            gyldigtNavn = true;
        }
    }

    aktivHero = new Hero(navn);
    cout << "Ny helt oprettet: " << aktivHero->hentNavn() << endl;
}

void GameManager::loadHero()
{
    cout << "--- Vaelg en eksisterende helt ---\n";
    for (size_t i = 0; i < predefineredeHeros.size(); ++i)
    {
        cout << i + 1 << ". " << predefineredeHeros[i].hentNavn()
             << " HP: " << predefineredeHeros[i].hentMaxHP()
             << ", Styrke: " << predefineredeHeros[i].hentStyrke()
             << ", Level: " << predefineredeHeros[i].hentLevel()
             << ", Guld: " << predefineredeHeros[i].hentGuld()
             << endl;
    }

    cout << "Valg: ";
    int valg = Hjaelpefunktioner::hentGyldigtTal(1, predefineredeHeros.size());

    aktivHero = new Hero(predefineredeHeros[valg - 1]);
    cout << "Helt valgt: " << aktivHero->hentNavn() << endl;
}

void GameManager::opretGrotter()
{
    if (!aktivHero)
    {
        cout << "Kan ikke oprette grotter uden en aktiv helt.\n";
        return;
    }

    if (!grottegren)
    {
        grottegren = new GrotteGenerator(new StandardFjendeFactory(fjendeListe));
    }
    grotterne = grottegren->genererGrotter(aktivHero->hentLevel(), aktivHero->hentLevel());
}

bool GameManager::eventyrMenu()
{
    int valg;

    do
    {
        cout << "\n--- EVENTYR MENU ---\n";
        cout << "1. Kaemp mod en fjende\n";
        cout << "2. Udforsk en grotte\n";
        cout << "3. Vis inventar\n";
        cout << "4. Vaabensaelger\n";
        cout << "5. Tilbage til hovedmenu\n";
        cout << "Valg: ";

        valg = Hjaelpefunktioner::hentGyldigtTal(1, 5);

        switch (valg)
        {
        case 1:
            kaempModFjende();
            if (!aktivHero->erILive())
            {
                return true;
            }
            break;
        case 2:
            opretGrotter();
            if (vaelgOgGennemfoerGrotte())
            {
                return true;
            }
            break;
        case 3:
            visInventarMenu();
            if (!aktivHero->erILive())
            {
                return true;
            }
            break;
        case 4:
            visVaabenSaelgerMenu();
            if (!aktivHero->erILive())
            {
                return true;
            }
            break;
        case 5:
            gemAktivHero();
            cout << "Tilbage til hovedmenu...\n";
            return true;
        default:
            cout << "Ugyldigt valg. Proev igen.\n";
        }

    } while (valg != 5 && aktivHero->erILive());
    return true;
}

void GameManager::kaempModFjende()
{
    Fjende fjende = vaelgFjende();
    cout << "--- KAMP ---\n";
    cout << aktivHero->hentNavn() << " kaemper mod " << fjende.hentNavn() << "!\n\n";

    cout << aktivHero->hentNavn() << " har\n"
         << "HP: " << aktivHero->hentHP() << "\n";

    const Vaaben *aktueltVaaben = aktivHero->hentUdstyretVaaben();

    if (aktueltVaaben != nullptr)
    {
        cout << "Vaaben: " << aktueltVaaben->hentNavn()
             << " (" << aktueltVaaben->hentNuvaerendeHoldbarhed()
             << "/" << aktueltVaaben->hentMaxHoldbarhed() << ")\n";

        aktivHero->brugAktivVaaben();
    }
    else
    {
        cout << "styrke: " << aktivHero->hentStyrke() << "\n\n";
    }

    cout << fjende.hentNavn() << " har\n"
         << "HP: " << fjende.hentHP() << "\n"
         << "styrke: " << fjende.hentStyrke() << "\n\n";

    while (aktivHero->erILive() && fjende.erILive())
    {
        cout << "Tryk paa ENTER for at angribe!\n";

        string input;
        getline(cin, input);
        if (input.empty())
        {
            cout << aktivHero->hentNavn() << " rammer " << fjende.hentNavn() << " for ";
            if (aktivHero->hentUdstyretVaaben())
            {
                cout << aktivHero->hentSkadeMedVaaben() << " skade!\n";
                fjende.tagSkade(aktivHero->hentSkadeMedVaaben());
            }
            else
            {
                cout << aktivHero->hentStyrke() << " skade!\n";
                fjende.tagSkade(aktivHero->hentStyrke());
            }
        }
        else
        {
            cout << aktivHero->hentNavn() << " fumler og rammer ikke!\n";
        }

        if (fjende.hentNavn() == "Dragon" && !fjende.erILive())
        {
            cout << "Du besejrede dragen! Du har vundet spillet!\n";
            cout << "Tillykke, " << aktivHero->hentNavn() << "!\n";
            cout << "Forlader spillet...\n";
            exit(0);
        }

        if (!fjende.erILive())
        {
            break;
        }

        cout << fjende.hentNavn() << " har " << fjende.hentHP() << " HP tilbage.\n\n";
        cout << fjende.hentNavn() << " rammer " << aktivHero->hentNavn() << " for " << fjende.hentStyrke() << " skade!\n";

        aktivHero->tagSkade(fjende.hentStyrke());

        if (!aktivHero->erILive())
        {
            break;
        }

        cout << aktivHero->hentNavn() << " har " << aktivHero->hentHP() << " HP tilbage.\n\n";
    }

    if (aktivHero->erILive())
    {
        aktivHero->givFuldHP();
        // Murloc faar double XP
        if (aktivHero->hentNavn() == "Murloc")
        {
            cout << aktivHero->hentNavn() << " vandt og faar double XP! " << aktivHero->hentNavn() << " faar derfor " << fjende.hentXPGevinst() * 2 << " XP!\n";
            aktivHero->givXP(fjende.hentXPGevinst() * 2);
        }
        else
        {
            cout << aktivHero->hentNavn() << " vandt og faar " << fjende.hentXPGevinst() << " XP!\n";
            aktivHero->givXP(fjende.hentXPGevinst());
        }

        while (aktivHero->levelOp())
        {
            aktivHero->givFuldHP();
            cout << "Du er steget i level!\n";
            cout << "Nyt level: " << aktivHero->hentLevel() << "\n";
            cout << "Nyt max HP: " << aktivHero->hentMaxHP() << "\n";
            cout << "Nyt styrke: " << aktivHero->hentStyrke() << "\n";
        }
        cout << "Du har nu " << aktivHero->hentXP() << " XP.\n";
    }
    else
    {
        cout << aktivHero->hentNavn() << " doede i kampen...\n";
    }
}

// Denne funktion er naesten identisk med kaempModFjende, men den tager en fjende som parameter
// og kaemper mod den i stedet for at vaelge en fra listen.
void GameManager::kaempModFjendeIGrotte(const Fjende &fjende)
{
    Fjende kopi = fjende;

    cout << "--- GROTTEKAMP ---\n";
    cout << aktivHero->hentNavn() << " kaemper mod " << kopi.hentNavn() << "!\n\n";

    cout << aktivHero->hentNavn() << " har\n"
         << "HP: " << aktivHero->hentHP() << "\n";

    const Vaaben *aktueltVaaben = aktivHero->hentUdstyretVaaben();

    if (aktueltVaaben != nullptr)
    {
        cout << "Vaaben: " << aktueltVaaben->hentNavn()
             << " (" << aktueltVaaben->hentNuvaerendeHoldbarhed()
             << "/" << aktueltVaaben->hentMaxHoldbarhed() << ")\n";

        aktivHero->brugAktivVaaben();
    }
    else
    {
        cout << "styrke: " << aktivHero->hentStyrke() << "\n\n";
    }

    cout << kopi.hentNavn() << " har\n"
         << "HP: " << kopi.hentHP() << "\n"
         << "styrke: " << kopi.hentStyrke() << "\n\n";

    while (aktivHero->erILive() && kopi.erILive())
    {
        cout << "Tryk paa ENTER for at angribe!\n";

        string input;
        getline(cin, input);
        if (input.empty())
        {
            cout << aktivHero->hentNavn() << " rammer " << kopi.hentNavn() << " for ";
            if (aktivHero->hentUdstyretVaaben())
            {
                cout << aktivHero->hentSkadeMedVaaben() << " skade!\n";
                kopi.tagSkade(aktivHero->hentSkadeMedVaaben());
            }
            else
            {
                cout << aktivHero->hentStyrke() << " skade!\n";
                kopi.tagSkade(aktivHero->hentStyrke());
            }
        }
        else
        {
            cout << aktivHero->hentNavn() << " fumler og rammer ikke!\n";
        }

        if (!kopi.erILive())
        {
            break;
        }

        cout << kopi.hentNavn() << " har " << kopi.hentHP() << " HP tilbage.\n\n";
        cout << kopi.hentNavn() << " rammer " << aktivHero->hentNavn() << " for " << kopi.hentStyrke() << " skade!\n";

        aktivHero->tagSkade(kopi.hentStyrke());

        if (!aktivHero->erILive())
        {
            break;
        }

        cout << aktivHero->hentNavn() << " har " << aktivHero->hentHP() << " HP tilbage.\n\n";
    }

    if (aktivHero->erILive())
    {
        aktivHero->givFuldHP();
        // Murloc faar double XP
        if (aktivHero->hentNavn() == "Murloc")
        {
            cout << aktivHero->hentNavn() << " vandt og faar double XP! " << aktivHero->hentNavn() << " faar derfor " << fjende.hentXPGevinst() * 2 << " XP!\n";
            aktivHero->givXP(kopi.hentXPGevinst() * 2);
        }
        else
        {
            cout << aktivHero->hentNavn() << " vandt og faar " << kopi.hentXPGevinst() << " XP!\n";
            aktivHero->givXP(kopi.hentXPGevinst());
        }

        if (aktivHero->levelOp())
        {
            aktivHero->givFuldHP();
            cout << "Du er steget i level!\n";
            cout << "Nyt level: " << aktivHero->hentLevel() << "\n";
            cout << "Nyt max HP: " << aktivHero->hentMaxHP() << "\n";
            cout << "Nyt styrke: " << aktivHero->hentStyrke() << "\n";
        }
        cout << "Du har nu " << aktivHero->hentXP() << " XP.\n";
    }
    else
    {
        cout << aktivHero->hentNavn() << " doede i kampen...\n";
    }
}

void GameManager::visFjender() const
{
    for (size_t i = 0; i < fjendeListe.size(); ++i)
    {
        cout << i + 1 << ". " << fjendeListe[i].hentNavn() << " (HP: "
             << fjendeListe[i].hentMaxHP() << ", Styrke: "
             << fjendeListe[i].hentStyrke() << ")\n";
    }
}

Fjende GameManager::vaelgFjende()
{
    cout << "--- Vaelg en fjende ---\n";
    visFjender();
    int valg;
    valg = Hjaelpefunktioner::hentGyldigtTal(1, fjendeListe.size());
    return fjendeListe[valg - 1];
}

void GameManager::opretFjender()
{
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

bool GameManager::vaelgOgGennemfoerGrotte()
{
    cout << "--- Vaelg en grotte ---\n";
    for (size_t i = 0; i < grotterne.size(); ++i)
    {
        cout << i + 1 << ": " << grotterne[i].hentNavn() << " (Guld: " << grotterne[i].hentGuld() << ")\n";

        cout << "   Fjender: ";
        const vector<Fjende> &fjender = grotterne[i].hentFjender();
        for (size_t j = 0; j < fjender.size(); ++j)
        {
            cout << fjender[j].hentNavn();
            if (j != fjender.size() - 1)
            {
                cout << ",\n            ";
            }
        }
        cout << endl
             << endl;
    }

    int valg = Hjaelpefunktioner::hentGyldigtTal(1, grotterne.size());
    Grotte valgt = grotterne[valg - 1];

    for (Fjende fjende : valgt.hentFjender())
    {
        cout << "Du moeder: " << fjende.hentNavn() << "\n";
        kaempModFjendeIGrotte(fjende);
        if (!aktivHero->erILive())
        {
            cout << "Du er doed og kan ikke fortsaette eventyret.\n";
            return true;
        }
    }

    aktivHero->givGuld(valgt.hentGuld());
    cout << "Du har gennemfoert " << valgt.hentNavn() << " og faar " << valgt.hentGuld() << " guld!\n";
    cout << "Du har nu " << aktivHero->hentGuld() << " guld.\n";

    // Rydder alle grotter saadan at der dannes nye grotter naeste gang
    grotterne.clear();

    return false;
}

void GameManager::visInventarMenu()
{
    int valg;
    if (!aktivHero)
    {
        cout << "Ingen aktiv helt!\n";
        return;
    }
    else if (aktivHero->hentAntalVaaben() == 0)
    {
        cout << "Ingen vaaben i inventar!\n";
        return;
    }
    do
    {
        aktivHero->visInventar();
        cout << "\n1. Udstyr vaaben\n"
             << "2. Tilbage til eventyrmenu\n"
             << "Valg: ";

        valg = Hjaelpefunktioner::hentGyldigtTal(1, 2);

        if (valg == 1)
        {
            cout << "Vaelg vaaben (1-" << aktivHero->hentAntalVaaben() << "): ";
            int valgAfVaaben = Hjaelpefunktioner::hentGyldigtTal(1, aktivHero->hentAntalVaaben());

            if (aktivHero->udstyrMedVaabenFraIndex(valgAfVaaben - 1))
            {
                cout << "Du har nu udstyret "
                     << aktivHero->hentUdstyretVaaben()->hentNavn() << "!\n";
            }
            else
            {
                cout << "Kunne ikke udstyre vaaben!\n";
            }
        }
    } while (valg != 2);
}

void GameManager::visVaabenSaelgerMenu()
{
    if (!aktivHero)
    {
        cout << "Ingen aktiv helt!\n";
        return;
    }

    static VaabenSaelger vaabenSaelger("Jeff");
    vaabenSaelger.fyldLager(aktivHero->hentLevel());

    int valg;
    do
    {
        cout << "\n--- VAABENHANDLER MENU ---\n";
        cout << "Du har " << aktivHero->hentGuld() << " guld." << "\n\n";

        // Vis vaabenudvalg med spillerns specifikke skadevaerdier
        vaabenSaelger.visLager(*aktivHero);

        cout << "\n1. Koeb vaaben\n"
             << "2. Tilbage til eventyrmenu\n"
             << "Valg: ";

        valg = Hjaelpefunktioner::hentGyldigtTal(1, 2);

        if (valg == 1)
        {
            cout << "Vaelg vaaben (1-" << vaabenSaelger.hentAntalVaaben() << ", 0 for at afbryde): ";
            int valgAfVaaben = Hjaelpefunktioner::hentGyldigtTal(0, vaabenSaelger.hentAntalVaaben());

            if (valgAfVaaben > 0)
            {
                vaabenSaelger.saelgVaaben(valgAfVaaben - 1, *aktivHero);
            }
            else
            {
                cout << "Koeb af vaaben afbrudt.\n";
            }
        }
    } while (valg != 2);
}

void GameManager::opretPredefineredeHeros()
{
    predefineredeHeros.push_back(Hero("Murloc", 4, 4, 1, 0, 1, 0));
    predefineredeHeros.push_back(Hero("Thor", 14, 14, 4, 0, 4, 0));
    predefineredeHeros.push_back(Hero("Loke", 8, 8, 6, 0, 3, 0));
    predefineredeHeros.push_back(Hero("Odin", 18, 18, 3, 0, 5, 0));
}

void GameManager::opretGemteHeros()
{
    vector<Hero> heros;
    if (heroRepository.indlaesHeros(heros))
    {
        gemteHeros = heros;
        cout << "Antal gemte helte: " << gemteHeros.size() << endl;
    }
    else
    {
        cout << "Ingen gemte helte fundet.\n";
    }
}

void GameManager::gemAktivHero()
{
    if (aktivHero)
    {
        if (aktivHero->hentUdstyretVaaben() != nullptr)
        {
            aktivHero->udrustVaaben(const_cast<Vaaben *>(aktivHero->hentUdstyretVaaben()));
        }

        if (heroRepository.gemHero(*aktivHero))
        {
            cout << "Helt gemt succesfuldt!\n";
            opretGemteHeros(); // Opdater listen med gemte helte
        }
        else
        {
            cout << "Fejl ved gemning af helt\n";
        }
    }
}

void GameManager::indlaesHeros()
{
    vector<Hero> heros;
    if (heroRepository.indlaesHeros(heros))
    {
        cout << "Antal indlaeste heros: " << heros.size() << endl;
        for (const auto &hero : heros)
        {
            cout << "Navn: " << hero.hentNavn()
                 << " (HP: " << hero.hentMaxHP()
                 << ", Styrke: " << hero.hentStyrke()
                 << ", XP: " << hero.hentXP()
                 << ", Level " << hero.hentLevel()
                 << " Guld: " << hero.hentGuld() << ")\n";
        }
    }
    else
    {
        cout << "Du har ikke tidligere gemt nogle helte!\n";
    }
}

GameManager::~GameManager()
{
    gemAktivHero();
    if (aktivHero)
    {
        delete aktivHero;
        aktivHero = nullptr;
    }
    if (grottegren)
    {
        delete grottegren;
        grottegren = nullptr;
    }
}