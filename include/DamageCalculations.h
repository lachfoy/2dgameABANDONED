#ifndef DAMAGECALCULATIONS_H
#define DAMAGECALCULATIONS_H

struct Damage
{
    int standard;
    int crushing;
};

// resistance is a value from 0 to 100 that determines the percent of damage that goes through
struct Resistance
{
    int standard;
    int crushing;
};

class DamageCalculations
{
public:
    static int damageAfterRestistance(const Damage& damage, const Resistance& resistance)
    {
        int standardDmgAvoided = (int)((resistance.standard / 100.0f) * damage.standard);
        int crushingDmgAvoided = (int)((resistance.crushing / 100.0f) * damage.crushing);    
        printf("avoided %i standard damage\n", standardDmgAvoided);
        printf("avoided %i crushing damage\n", crushingDmgAvoided);

        int total = damage.standard + damage.crushing - standardDmgAvoided - crushingDmgAvoided;
        printf("took %i total damage\n", total);

        return total;
    }
};

#endif