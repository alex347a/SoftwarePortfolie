#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <sqlite3.h>

#include <string>
#include <vector>

using namespace std;

class DatabaseManager
{
public:
    DatabaseManager(const string &dbSti);

    sqlite3* hentDB() const { return db; }

    bool eksekverSQLData(const string &sql);                                       // Til CREATE/INSERT/UPDATE
    bool forespoergSQLData(const string &sql, vector<vector<string>> &resultater); // Til SELECT

    ~DatabaseManager();

private:
    sqlite3 *db;
};

#endif