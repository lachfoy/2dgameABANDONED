#ifndef DYNAMICHEALTHBAR_H
#define DYNAMICHEALTHBAR_H

#include "Healthbar.h"

class BaseDamageable;

class DynamicHealthbar : public Healthbar
{
public:
    DynamicHealthbar(int length, int height, BaseDamageable* damageable);

    // updates the position of the healthbar around a center origin
    void updatePosition() override;

};

#endif