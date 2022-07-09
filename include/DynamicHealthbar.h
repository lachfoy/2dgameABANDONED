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
    int newX = (int)damageable->posX;
    int newY = (int)damageable->posY - damageable->getHeight() - height - 2; // newY - objH - healthbarH - some padding value

    this->x = newX - (int)(length / 2.0f);
    this->y = newY - (int)(height / 2.0f);

    bg_rect.x = this->x;
    bg_rect.y = this->y;

    health_rect.x = this->x;
    health_rect.y = this->y;
} 

#endif