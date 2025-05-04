#include "Grotte.h"

using namespace std;

Grotte::Grotte() {}

Grotte::Grotte(string navn, int guld, vector<Fjende> fjender)
    : navn(navn), guld(guld), fjender(fjender) {}

const string& Grotte::hentNavn() const 
{
    return navn;
}

int Grotte::hentGuld() const 
{
    return guld;
}

const vector<Fjende>& Grotte::hentFjender() const 
{
    return fjender;
}

Grotte::~Grotte() {}