#ifndef KAMPMANAGER_H
#define KAMPMANAGER_H

#include "Hero.h"
#include "Fjende.h"
#include "Vaaben.h"
#include "Analyse.h"
#include "DatabaseManager.h"

#include <iostream>

class KampManager {
public:
    // Returnerer true hvis helten overlever, false hvis helten dør
    static bool kaemp(Hero& hero, Fjende& fjende, Analyse& analyse, DatabaseManager& dbManager);
};

#endif