#ifndef RESISTANCE_H
#define RESISTANCE_H

#include "Damage.h"

// resistance is a value from 0 to 100 that determines the percent of damage that goes through
struct Resistance
{
    int standardResistance;
    int crushingResistance;

    int damageAfterRestistance(const Damage& damage) const
    {
        printf("taking %i standard damage\n", damage.standard);
        printf("taking %i crushing damage\n", damage.crushing);

        int standardDmgAvoided = (int)((standardResistance / 100.0f) * damage.standard);
        int crushingDmgAvoided = (int)((crushingResistance / 100.0f) * damage.crushing);    
        printf("avoided %i standard damage\n", standardDmgAvoided);
        printf("avoided %i crushing damage\n", crushingDmgAvoided);

        int total = damage.standard + damage.crushing - standardDmgAvoided - crushingDmgAvoided;
        printf("took %i total damage\n", total);

        return total;
    }
};

#endif