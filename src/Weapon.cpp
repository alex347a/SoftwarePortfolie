#include "Weapon.h"

using namespace std;

Weapon::Weapon(string name, int baseDamage, int scalingFactor, int durability)
    : name(name), baseDamage(baseDamage), scalingFactor(scalingFactor), maxDurability(durability), currentDurability(durability) {}

string Weapon::getName() const {
    return name;
}

int Weapon::getTotalDamage(int heroBaseDamage) const {
    return baseDamage + scalingFactor * heroBaseDamage;
}

int Weapon::getCurrentDurability() const {
    return currentDurability;
}

void Weapon::use() {
    if (currentDurability > 0) {
        currentDurability--;
    }
}

bool Weapon::isBroken() const {
    return currentDurability <= 0;
}