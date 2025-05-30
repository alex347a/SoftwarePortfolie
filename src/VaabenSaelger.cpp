#include "VaabenSaelger.h"

VaabenSaelger::VaabenSaelger(const string &saelgerNavn, DatabaseManager &dbManager) : saelgerNavn(saelgerNavn), dbManager(dbManager)
{
    fyldLager(1);
}

int VaabenSaelger::hentAntalVaaben() const
{
    return vaabenLager.size();
}

void VaabenSaelger::visLager(const Hero &koeber) const
{
    cout << "\n=== " << saelgerNavn << "'s Vaabenudvalg ===\n";
    for (size_t i = 0; i < hentAntalVaaben(); ++i)
    {
        cout << i + 1 << ". " << vaabenLager[i].hentNavn()
             << " (" << vaabenLager[i].hentTotalStyrke(koeber.hentStyrke()) << " skade) - "
             << beregnPris(vaabenLager[i], koeber.hentStyrke()) << " guld\n";
    }
    cout << "0. Afbryd\n";
}

void VaabenSaelger::fyldLager(int level)
{
    vaabenLager.clear();
    vaabenLager.push_back(Vaaben("Jernsvaerd", 5, 1, 20));
    vaabenLager.push_back(Vaaben("Hammer", 3, 2, 30));
    vaabenLager.push_back(Vaaben("Staaloekse", 8, 3, 15));
}

int VaabenSaelger::beregnPris(const Vaaben &vaaben, int heroStyrke) const
{
    return 30 + (vaaben.hentTotalStyrke(heroStyrke) * 10);
}

bool VaabenSaelger::saelgVaaben(int index, Hero &koeber)
{
    if (index < 0 || index >= hentAntalVaaben())
    {
        cout << "Ugyldigt vaabenvalg!\n";
        return false;
    }

    int pris = beregnPris(vaabenLager[index], koeber.hentStyrke());

    if (koeber.hentGuld() >= pris)
    {
        const Vaaben &v = vaabenLager[index];

        // Find vaaben_type_id i databasen (eller opret hvis den ikke findes i forvejen)
        int typeId = -1;
        sqlite3_stmt *stmt;
        const char *findTypeSQL = "SELECT id FROM VaabenTyper WHERE navn = ?";
        if (sqlite3_prepare_v2(dbManager.hentDB(), findTypeSQL, -1, &stmt, nullptr) == SQLITE_OK)
        {
            sqlite3_bind_text(stmt, 1, v.hentNavn().c_str(), -1, SQLITE_TRANSIENT);
            if (sqlite3_step(stmt) == SQLITE_ROW)
                typeId = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
        }
        // Hvis ikke fundet, opret ny type
        if (typeId == -1)
        {
            const char *insertTypeSQL = "INSERT INTO VaabenTyper (navn, baseStyrke, skaleringsFaktor, maxHoldbarhed) VALUES (?, ?, ?, ?)";
            if (sqlite3_prepare_v2(dbManager.hentDB(), insertTypeSQL, -1, &stmt, nullptr) == SQLITE_OK)
            {
                sqlite3_bind_text(stmt, 1, v.hentNavn().c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_int(stmt, 2, v.hentBaseStyrke());
                sqlite3_bind_double(stmt, 3, v.hentSkaleringsFaktor());
                sqlite3_bind_int(stmt, 4, v.hentMaxHoldbarhed());
                sqlite3_step(stmt);
                sqlite3_finalize(stmt);
            }
            typeId = sqlite3_last_insert_rowid(dbManager.hentDB());
        }

        // Indsaet vaaben med korrekt typeId
        string sql = "INSERT INTO Vaaben (vaaben_type_id, nuvaerendeHoldbarhed) VALUES (?, ?)";
        if (sqlite3_prepare_v2(dbManager.hentDB(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
        {
            sqlite3_bind_int(stmt, 1, typeId);
            sqlite3_bind_int(stmt, 2, v.hentNuvaerendeHoldbarhed());
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
        int vaabenId = sqlite3_last_insert_rowid(dbManager.hentDB());

        Vaaben vaabenKopi = v;
        vaabenKopi.saetVaabenId(vaabenId);
        vaabenKopi.saetVaabenTypeId(typeId);

        koeber.tilfoejVaaben(vaabenKopi);
        koeber.givGuld(-pris);
        cout << "Koebet gennemfoert: " << vaabenLager[index].hentNavn() << " for " << pris << " guld\n";
        return true;
    }

    cout << "Ikke nok guld! Du har " << koeber.hentGuld() << ", men skal bruge " << pris << "\n";
    return false;
}