#ifndef RESISTANCE_H
#define RESISTANCE_H

#include "Damage.h"

// resistance is a value from -100 to 100 that determines the percent of damage that goes through
struct Resistance
{
    int standardResistance;
    int crushingResistance;
    int fireResistance;

    int damageAfterRestistance(const Damage& damage) const
    {
        int standardDmg = damage.standard - (int)((standardResistance / 100.0f) * damage.standard);
        int crushingDmg = damage.crushing - (int)((crushingResistance / 100.0f) * damage.crushing);  
        int fireDmg = damage.fire - (int)((fireResistance / 100.0f) * damage.fire);   

        int total = standardDmg + crushingDmg + fireDmg;

        return total;
    }
};

#endif