#include "Hero.h"

// Constructor til Hero med custom navn
Hero::Hero(string navn)
    : Karakter(navn, 10, 10, 2), xp(0), level(1), guld(0), aktivVaaben(nullptr), id(0) {}

// Constructor til predefinerede Heros
Hero::Hero(string navn, int maxHP, int hp, int styrke, int xp, int level, int guld)
    : Karakter(navn, maxHP, hp, styrke), xp(xp), level(level), guld(guld), aktivVaaben(nullptr), id(0) {}

int Hero::hentLevel() const
{
    return level;
}

int Hero::hentXP() const
{
    return xp;
}

int Hero::hentGuld() const
{
    return guld;
}

int Hero::hentStyrke() const
{
    return styrke;
}

int Hero::hentSkadeMedVaaben() const
{
    if (aktivVaaben && !aktivVaaben->erOedelagt())
    {
        return aktivVaaben->hentTotalStyrke(styrke);
    }
    return styrke;
}

int Hero::hentAntalVaaben() const
{
    return inventar.size();
}

void Hero::givFuldHP()
{
    hp = maxHP;
}

void Hero::givXP(int xpMaengde)
{
    xp += xpMaengde;
}

void Hero::givGuld(int guldMaengde)
{
    guld += guldMaengde;
}

void Hero::tilfoejVaaben(Vaaben vaaben)
{
    inventar.push_back(vaaben);
}

void Hero::setAktivVaaben(Vaaben *vaaben)
{
    aktivVaaben = vaaben;
}

void Hero::udrustVaaben(Vaaben *vaaben)
{
    aktivVaaben = nullptr;
}

void Hero::visInventar() const
{
    if (inventar.empty())
    {
        cout << "Ingen vaaben i inventar!\n";
        return;
    }

    cout << "=== Vaaben inventar ===\n";
    for (size_t i = 0; i < inventar.size(); ++i)
    {
        cout << i + 1 << ". " << inventar[i].hentNavn()
             << " (Skade: +" << inventar[i].hentTotalStyrke(styrke)
             << ", Holdbarhed: " << inventar[i].hentNuvaerendeHoldbarhed()
             << "/" << inventar[i].hentMaxHoldbarhed() << ")";

        if (aktivVaaben == &inventar[i])
        {
            cout << " [UDSTYRET]";
        }
        cout << "\n";
    }
}

void Hero::brugAktivVaaben()
{
    aktivVaaben->brug();
    if (aktivVaaben->erOedelagt())
    {
        cout << aktivVaaben->hentNavn() << " er oedelagt!\n";
        aktivVaaben = nullptr;
    }
}

bool Hero::levelOp()
{
    int levelGraense = level * 1000;
    if (xp >= levelGraense)
    {
        xp -= levelGraense;
        level++;
        maxHP += 2;
        styrke += 1;
        return true;
    }
    return false;
}

bool Hero::udstyrMedVaabenFraIndex(int index)
{
    if (index < 0 || index >= inventar.size())
    {
        cout << "Ikke et validt vaabenindeks!\n";
        return false;
    }
    aktivVaaben = &inventar[index];
    return true;
}

const Vaaben *Hero::hentUdstyretVaaben() const
{
    return aktivVaaben;
}

vector<Vaaben> Hero::hentAlleVaaben() const
{
    return inventar;
}

void Hero::saetDatabaseId(int id)
{
    this->id = id;
}

int Hero::hentDatabaseId() const
{
    return id;
}