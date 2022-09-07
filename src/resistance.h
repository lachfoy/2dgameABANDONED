#ifndef RESISTANCE_H_
#define RESISTANCE_H_

#include "damage.h"

// resistance is a value from -100 to 100 that determines the percent of damage that goes through
struct Resistance
{
    int standard_resistance;
    int crushing_resistance;
    int fire_resistance;
    int magic_resistance;
    int poison_resistance;

    int damageAfterRestistance(const Damage& damage) const
    {
        int standard_dmg = damage.standard - (int)((standard_resistance / 100.0f) * damage.standard);
        int crushing_dmg = damage.crushing - (int)((crushing_resistance / 100.0f) * damage.crushing);
        int fire_dmg = damage.fire - (int)((fire_resistance / 100.0f) * damage.fire);
        int magic_dmg = damage.magic - (int)((magic_resistance / 100.0f) * damage.magic);
        int poison_dmg = damage.poison - (int)((poison_resistance / 100.0f) * damage.poison);

        int total = standard_dmg + crushing_dmg + fire_dmg + magic_dmg + poison_dmg;

        return total;
    }
};

#endif