#include "KampManager.h"
#include <sqlite3.h>

using namespace std;

bool KampManager::kaemp(Hero& hero, Fjende& fjende, Analyse& analyse, DatabaseManager& dbManager)
{
    cout << "--- KAMP ---\n";
    cout << hero.hentNavn() << " kaemper mod " << fjende.hentNavn() << "!\n\n";
    cout << hero.hentNavn() << " har\n"
         << "HP: " << hero.hentHP() << "\n";
    const Vaaben *aktueltVaaben = hero.hentUdstyretVaaben();
    if (aktueltVaaben != nullptr)
    {
        cout << "Vaaben: " << aktueltVaaben->hentNavn()
             << " (" << aktueltVaaben->hentNuvaerendeHoldbarhed()
             << "/" << aktueltVaaben->hentMaxHoldbarhed() << ")\n";
        hero.brugAktivVaaben();
    }
    else
    {
        cout << "styrke: " << hero.hentStyrke() << "\n\n";
    }
    cout << fjende.hentNavn() << " har\n"
         << "HP: " << fjende.hentHP() << "\n"
         << "styrke: " << fjende.hentStyrke() << "\n\n";
    while (hero.erILive() && fjende.erILive())
    {
        cout << "Tryk paa ENTER for at angribe!\n";
        string input;
        getline(cin, input);
        if (input.empty())
        {
            cout << hero.hentNavn() << " rammer " << fjende.hentNavn() << " for ";
            if (hero.hentUdstyretVaaben())
            {
                cout << hero.hentSkadeMedVaaben() << " skade!\n";
                fjende.tagSkade(hero.hentSkadeMedVaaben());
            }
            else
            {
                cout << hero.hentStyrke() << " skade!\n";
                fjende.tagSkade(hero.hentStyrke());
            }
        }
        else
        {
            cout << hero.hentNavn() << " fumler og rammer ikke!\n";
        }
        if (!fjende.erILive())
            break;
        cout << fjende.hentNavn() << " har " << fjende.hentHP() << " HP tilbage.\n\n";
        cout << fjende.hentNavn() << " rammer " << hero.hentNavn() << " for " << fjende.hentStyrke() << " skade!\n";
        hero.tagSkade(fjende.hentStyrke());
        if (!hero.erILive())
            break;
        cout << hero.hentNavn() << " har " << hero.hentHP() << " HP tilbage.\n\n";
    }

    // Efter kampen: XP, analyse, level-op
    if (hero.erILive())
    {
        hero.givFuldHP();
        // Murloc får dobbelt XP
        if (hero.hentNavn() == "Murloc")
        {
            cout << hero.hentNavn() << " vandt og faar double XP! " << hero.hentNavn() << " faar derfor " << fjende.hentXPGevinst() * 2 << " XP!\n";
            hero.givXP(fjende.hentXPGevinst() * 2);
        }
        else
        {
            cout << hero.hentNavn() << " vandt og faar " << fjende.hentXPGevinst() << " XP!\n";
            hero.givXP(fjende.hentXPGevinst());
        }

        while (hero.levelOp())
        {
            hero.givFuldHP();
            cout << hero.hentNavn() << " er steget i level!\n";
            cout << "Nyt level: " << hero.hentLevel() << "\n";
            cout << "Nyt max HP: " << hero.hentMaxHP() << "\n";
            cout << "Nyt styrke: " << hero.hentStyrke() << "\n";
        }
        cout << hero.hentNavn() << " har nu " << hero.hentXP() << " XP.\n";

        // Analyse/statistik (indsæt i Analyse-tabellen)
        int heroId = hero.hentDatabaseId();
        const Vaaben *vaaben = hero.hentUdstyretVaaben();
        int vaabenId = vaaben ? vaaben->hentVaabenId() : 0;

        string sql = "INSERT INTO Analyse (hero_id, vaaben_id) VALUES (?, ?)";
        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(dbManager.hentDB(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
        {
            sqlite3_bind_int(stmt, 1, heroId);
            if (vaabenId > 0)
                sqlite3_bind_int(stmt, 2, vaabenId);
            else
                sqlite3_bind_null(stmt, 2);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
        else
        {
            cerr << "Fejl: " << sqlite3_errmsg(dbManager.hentDB()) << endl;
        }
    }
    else
    {
        cout << hero.hentNavn() << " doede i kampen...\n";
        cout << "Din helt gaar tilbage til sidste gemte tilstand.\n";
    }
    return hero.erILive();
}