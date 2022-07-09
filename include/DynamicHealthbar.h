#ifndef DYNAMICHEALTHBAR_H
#define DYNAMICHEALTHBAR_H

#include "Healthbar.h"

class BaseDamageable;

class DynamicHealthbar : public Healthbar
{
public:
    DynamicHealthbar(int length, int height, BaseDamageable* damageable)
         : Healthbar(0, 0, length, height, damageable) {}
    ~DynamicHealthbar() override {}

    // updates the position of the healthbar around a center origin
    inline void updatePosition() override;
};

#include "BaseDamageable.h"

void DynamicHealthbar::updatePosition()
{
    bg_rect.x = damageable->posX - (int)(length / 2);
    bg_rect.y = damageable->posY - (int)(height / 2);

    health_rect.x = damageable->posX - (int)(length / 2);
    health_rect.y = damageable->posY - (int)(height / 2);
} 

#endif