#include "Analyse.h"

Analyse::Analyse(DatabaseManager &dbManager) : dbManager(dbManager) {}

vector<string> Analyse::hentSorteredeHelteNavne()
{
    vector<vector<string>> resultater;
    string sql = "SELECT navn FROM Hero ORDER BY navn ASC";

    if (dbManager.forespoergSQLData(sql, resultater))
    {
        vector<string> helteNavne;
        for (const auto &raekke : resultater)
        {
            if (!raekke.empty())
            {
                helteNavne.push_back(raekke[0]);
            }
        }
        return helteNavne;
    }
    return {};
}

int Analyse::antalFjenderBesejretAfHero(int heroId)
{
    vector<vector<string>> resultater;
    string sql = "SELECT COUNT(*) FROM Analyse WHERE hero_id = " + to_string(heroId);

    if (dbManager.forespoergSQLData(sql, resultater))
    {
        if (!resultater.empty() && !resultater[0].empty())
        {
            return stoi(resultater[0][0]);
        }
    }
    return 0;
}

map<string, int> Analyse::fjenderBesejretPerVaabenForHero(int heroId)
{
    map<string, int> vaabenFjenderMap;
    vector<vector<string>> resultater;

    string sql = "SELECT vt.navn, COUNT(*) "
                 "FROM Analyse drab "
                 "JOIN Vaaben v ON drab.vaaben_id = v.id "
                 "JOIN VaabenTyper vt ON v.vaaben_type_id = vt.id "
                 "WHERE drab.hero_id = " +
                 to_string(heroId) + " "
                 "GROUP BY vt.navn";

    if (dbManager.forespoergSQLData(sql, resultater))
    {
        for (const auto &raekke : resultater)
        {
            if (raekke.size() == 2)
            {
                vaabenFjenderMap[raekke[0]] = stoi(raekke[1]);
            }
        }
    }
    return vaabenFjenderMap;
}

map<string, string> Analyse::mestDrabeligeHeroPerVaaben()
{
    map<string, string> vaabenHeroMap;
    vector<vector<string>> resultater;

    string sql =
        "SELECT vt.navn, h.navn "
        "FROM Analyse a "
        "JOIN Hero h ON a.hero_id = h.id "
        "JOIN Vaaben v ON a.vaaben_id = v.id "
        "JOIN VaabenTyper vt ON v.vaaben_type_id = vt.id "
        "GROUP BY vt.navn, h.navn "
        "HAVING COUNT(*) = ("
        "  SELECT MAX(antal) FROM ("
        "    SELECT COUNT(*) AS antal "
        "    FROM Analyse a2 "
        "    JOIN Vaaben v2 ON a2.vaaben_id = v2.id "
        "    JOIN VaabenTyper vt2 ON v2.vaaben_type_id = vt2.id "
        "    WHERE vt2.navn = vt.navn "
        "    GROUP BY a2.hero_id"
        "  )"
        ")";

    if (dbManager.forespoergSQLData(sql, resultater))
    {
        for (const auto &raekke : resultater)
        {
            if (raekke.size() == 2)
            {
                vaabenHeroMap[raekke[0]] = raekke[1];
            }
        }
    }
    return vaabenHeroMap;
}