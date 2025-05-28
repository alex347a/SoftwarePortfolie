#include "HeroRepository.h"
#include <iostream>

HeroRepository::HeroRepository(DatabaseManager &dbManager)
    : dbManager(dbManager) {}

// Gem en helt i databasen
bool HeroRepository::gemHero(const Hero &hero)
{
    // Starter en transaktion, saa jeg kan rulle tilbage, hvis noget gaar galt. Jeg skal baade gemme helten og vaaben.
    dbManager.eksekverSQLData("BEGIN TRANSACTION");

    // Saa vidt jeg kunne laese online, saa er det bedst practise at bruge en parametriseret forespoergelse fordi det sikrer en imod SQL-injection.
    const char *sql;
    if (hero.hentDatabaseId() == 0)
    {
        sql = "INSERT INTO Hero (navn, maxHP, hp, styrke, xp, level, guld) VALUES (?, ?, ?, ?, ?, ?, ?)";
    }
    else
    {
        sql = "UPDATE Hero SET navn = ?, maxHP = ?, hp = ?, styrke = ?, xp = ?, level = ?, guld = ? WHERE id = ?";
    }

    sqlite3_stmt *stmt;
    // -1 betyder at laengden af SQL-strengen bliver beregnet automatisk.
    if (sqlite3_prepare_v2(dbManager.hentDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Fejl under forberedelse af INSERT: " << sqlite3_errmsg(dbManager.hentDB()) << endl;
        return false;
    }

    // SQLITE_TRANSIENT betyder at SQLite kopierer strengen, saa hvis der sker noget med Hero-objektet, saa har det ikke indflydelse paa databasen.
    // sqlite3_bind_text bruger 1-baserede indeksering (i modsaetning til sqlite3_column).
    if (hero.hentDatabaseId() == 0)
    {
        sqlite3_bind_text(stmt, 1, hero.hentNavn().c_str(), -1, SQLITE_TRANSIENT); // navn
        sqlite3_bind_int(stmt, 2, hero.hentMaxHP());                               // maxHP
        sqlite3_bind_int(stmt, 3, hero.hentHP());                                  // hp
        sqlite3_bind_int(stmt, 4, hero.hentStyrke());                              // styrke
        sqlite3_bind_int(stmt, 5, hero.hentXP());                                  // xp       
        sqlite3_bind_int(stmt, 6, hero.hentLevel());                               // level
        sqlite3_bind_int(stmt, 7, hero.hentGuld());                                // guld
    }
    else
    {
        sqlite3_bind_text(stmt, 1, hero.hentNavn().c_str(), -1, SQLITE_TRANSIENT); // navn
        sqlite3_bind_int(stmt, 2, hero.hentMaxHP());                               // maxHP
        sqlite3_bind_int(stmt, 3, hero.hentHP());                                  // hp
        sqlite3_bind_int(stmt, 4, hero.hentStyrke());                              // styrke
        sqlite3_bind_int(stmt, 5, hero.hentXP());                                  // xp
        sqlite3_bind_int(stmt, 6, hero.hentLevel());                               // level
        sqlite3_bind_int(stmt, 7, hero.hentGuld());                                // guld
        sqlite3_bind_int(stmt, 8, hero.hentDatabaseId());                          // id (WHERE)                              // guld
    }

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cerr << "Fejl under INSERT: " << sqlite3_errmsg(dbManager.hentDB()) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // Hvis ny helt, hent det genererede ID
    if (hero.hentDatabaseId() == 0)
    {
        int nytId = sqlite3_last_insert_rowid(dbManager.hentDB());
        const_cast<Hero &>(hero).saetDatabaseId(nytId);
        cout << "Ny helt gemt med ID: " << nytId << endl;
    }

    sqlite3_finalize(stmt);

    // Vaaben gemmes
    const Vaaben *vaaben = hero.hentUdstyretVaaben();
    if (vaaben)
    {
        if (!gemHeroVaaben(hero.hentDatabaseId(), *vaaben))
        {
            // Hvis der er fejl ved at gemme vaaben, rulles aendringerne tilbage.
            cout << "Fejl ved gemning af vaaben for helt: " << hero.hentNavn() << endl;
            dbManager.eksekverSQLData("ROLLBACK");
            return false;
        }
    }

    // Hvis alt er gaaet godt, udfoeres handlingen.
    dbManager.eksekverSQLData("COMMIT");
    return true;
}

// Indlaes alle helte fra databasen
bool HeroRepository::indlaesHeros(vector<Hero> &heros)
{
    const char *sql = "SELECT id, navn, maxHP, hp, styrke, xp, level, guld FROM Hero";
    sqlite3_stmt *stmt;
    heros.clear();

    if (sqlite3_prepare_v2(dbManager.hentDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Fejl under forberedelse af SELECT: " << sqlite3_errmsg(dbManager.hentDB()) << endl;
        return false;
    }

    // Hver raekke returneres som en raekke af kolonner.
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        // Ligesom i DatabaseManager.cpp, saa skal jeg caste fra const unsigned char* til const char* for at hente teksten.
        // sqlite3_column bruger 0-baserede indeksering.
        int id = sqlite3_column_int(stmt, 0);
        string navn = (const char *)(sqlite3_column_text(stmt, 1));
        int maxHP = sqlite3_column_int(stmt, 2);
        int hp = sqlite3_column_int(stmt, 3);
        int styrke = sqlite3_column_int(stmt, 4);
        int xp = sqlite3_column_int(stmt, 5);
        int level = sqlite3_column_int(stmt, 6);
        int guld = sqlite3_column_int(stmt, 7);

        Hero hero(navn, maxHP, hp, styrke, xp, level, guld);
        hero.saetDatabaseId(id);

        auto vaaben = indlaesHeroVaaben(id);
        for (const auto &v : vaaben)
        {
            hero.tilfoejVaaben(v);
        }

        heros.push_back(hero);
    }

    sqlite3_finalize(stmt);
    return true;
}

bool HeroRepository::gemHeroVaaben(int heroId, const Vaaben &vaaben)
{
    const char *findVaabenSQL = "SELECT id FROM Vaaben WHERE navn = ?";
    sqlite3_stmt *stmt;

    // Tjek om vaaben allerede findes
    if (sqlite3_prepare_v2(dbManager.hentDB(), findVaabenSQL, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Fejl ved vaabensoegning: " << sqlite3_errmsg(dbManager.hentDB()) << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, vaaben.hentNavn().c_str(), -1, SQLITE_TRANSIENT);
    int vaabenId = -1;

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        vaabenId = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    // Hvis nyt vaaben, saa indsaet det
    if (vaabenId == -1)
    {
        const char *insertVaabenSQL = "INSERT INTO Vaaben (navn, baseStyrke, skaleringsFaktor, maxHoldbarhed) VALUES (?, ?, ?, ?)";
        if (sqlite3_prepare_v2(dbManager.hentDB(), insertVaabenSQL, -1, &stmt, nullptr) != SQLITE_OK)
        {
            cerr << "Fejl ved vaabenindsaettelse: " << sqlite3_errmsg(dbManager.hentDB()) << endl;
            return false;
        }

        sqlite3_bind_text(stmt, 1, vaaben.hentNavn().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, vaaben.hentBaseStyrke());
        sqlite3_bind_double(stmt, 3, vaaben.hentSkaleringsFaktor());
        sqlite3_bind_int(stmt, 4, vaaben.hentMaxHoldbarhed());

        if (sqlite3_step(stmt) != SQLITE_DONE)
        {
            sqlite3_finalize(stmt);
            return false;
        }

        vaabenId = sqlite3_last_insert_rowid(dbManager.hentDB());
        sqlite3_finalize(stmt);
    }

    // Link vaaben til helt
    const char *linkSQL = "INSERT OR REPLACE INTO HeroVaaben (hero_id, vaaben_id, nuvaerendeHoldbarhed) VALUES (?, (SELECT id FROM Vaaben WHERE navn = ?), ?)";
    if (sqlite3_prepare_v2(dbManager.hentDB(), linkSQL, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Fejl ved vaabenlink: " << sqlite3_errmsg(dbManager.hentDB()) << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, heroId);
    sqlite3_bind_int(stmt, 2, vaabenId);
    sqlite3_bind_int(stmt, 3, vaaben.hentNuvaerendeHoldbarhed());

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

vector<Vaaben> HeroRepository::indlaesHeroVaaben(int heroId)
{
    vector<Vaaben> vaabenListe;

    const char *sql = "SELECT v.navn, v.baseStyrke, v.skaleringsFaktor, "
                      "v.maxHoldbarhed, hv.nuvaerendeHoldbarhed "
                      "FROM HeroVaaben hv "
                      "JOIN Vaaben v ON hv.vaaben_id = v.id "
                      "WHERE hv.hero_id = ?";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(dbManager.hentDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Fejl ved indlaesning af vaaben: " << sqlite3_errmsg(dbManager.hentDB()) << endl;
        return vaabenListe;
    }

    sqlite3_bind_int(stmt, 1, heroId);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Vaaben vaaben(
            (const char *)sqlite3_column_text(stmt, 0), // navn
            sqlite3_column_int(stmt, 1),                // baseStyrke
            sqlite3_column_double(stmt, 2),             // skaleringsFaktor
            sqlite3_column_int(stmt, 3)                 // maxHoldbarhed
        );
        vaaben.setNuvaerendeHoldbarhed(sqlite3_column_int(stmt, 4));
        vaabenListe.push_back(vaaben);
    }

    sqlite3_finalize(stmt);
    return vaabenListe;
}