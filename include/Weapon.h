#ifndef WEAPON_H
#define WEAPON_H

#include <string>

using namespace std;

class Weapon {
public:
    Weapon(string name, int baseDamage, int scalingFactor, int durability);
    
    string getName() const;
    int getTotalDamage(int heroBaseDamage) const;
    int getCurrentDurability() const;

    void use();
    bool isBroken() const;
    
private:
    string name;
    int baseDamage;
    int scalingFactor;
    int maxDurability;
    int currentDurability;
};

#endif
