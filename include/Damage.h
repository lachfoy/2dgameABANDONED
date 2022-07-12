#ifndef DAMAGE_H
#define DAMAGE_H

struct Damage
{
    int standard;
    int crushing;
    int fire;
    bool setBurning;
};

namespace StatusDamage
{
    static const Damage burning = { .standard = 0, .crushing = 0, .fire = 4, .setBurning = false };
};

#endif