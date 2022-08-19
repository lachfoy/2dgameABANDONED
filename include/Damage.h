#ifndef DAMAGE_H_
#define DAMAGE_H_

struct Damage
{
    int standard;
    int crushing;
    int fire;
    int magic;
    int poison;
    bool setBurning; // should this projectile set the burning status
};

// predefined status damages
static const Damage statusBurning = {
    .standard = 0,
    .crushing = 0,
    .fire = 4, // only deals a small tick of fire damage
    .magic = 0,
    .poison = 0,
    .setBurning = false,
};

#endif