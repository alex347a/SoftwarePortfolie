#include "DatabaseManager.h"
#include <iostream>

// Foerst proever jeg at aabne databasen, og opretter en ny hvis den ikke findes
DatabaseManager::DatabaseManager(const string &dbSti)
{
    if (sqlite3_open(dbSti.c_str(), &db) != SQLITE_OK)
    {
        cerr << "Kan ikke aabne database: " << sqlite3_errmsg(db) << endl;
    }
}

// SQL forespoergslerne er til CREATE, INSERT, UPDATE og DELETE, som ikke returnerer noget
bool DatabaseManager::eksekverSQLData(const string &sql)
{
    char *fejlBesked = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &fejlBesked) != SQLITE_OK)
    {
        cerr << "SQL-fejl: " << fejlBesked << endl;
        sqlite3_free(fejlBesked);
        return false;
    }
    return true;
}

// SQL forespoergslerne er til SELECT, som returnerer resultater
bool DatabaseManager::forespoergSQLData(const string &sql, vector<vector<string>> &resultater)
{
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Fejl under forberedelse af forespoergsel: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    int kolonner = sqlite3_column_count(stmt);
    resultater.clear();

    // Gemmer resultaterne i en vektor, hvor hver raekke er en databasepost, og hver kolonne er en vaerdi.
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        vector<string> raekke;
        for (int i = 0; i < kolonner; ++i)
        {
            // Henter vaerdien fra den aktuelle kolonne i raekken
            // sqlite3_column_text returnerer en const unsigned char*, saa jeg er noedsaget til at caste den til const char*, da det er det en string i C++ forventer.
            const char *vaerdi = (const char *)sqlite3_column_text(stmt, i);
            // Gemmer vaerdien medmindre den er NULL
            raekke.push_back(vaerdi ? vaerdi : "NULL");
        }
        resultater.push_back(raekke);
    }

    // garbage collection
    sqlite3_finalize(stmt);
    return true;
}

DatabaseManager::~DatabaseManager()
{
    sqlite3_close(db);
}