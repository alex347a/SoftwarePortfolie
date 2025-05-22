#include "Hjaelpefunktioner.h"

int Hjaelpefunktioner::hentGyldigtTal(int min, int max)
{
    int valg;
    string input;

    while (true)
    {
        getline(cin, input);
        stringstream ss(input);

        if (ss >> valg && !(ss >> input))
        {
            if (valg >= min && valg <= max)
            {
                return valg;
            }
        }
        cout << "Indtast venligst et tal mellem " << min << " og " << max << ": ";
    }
}