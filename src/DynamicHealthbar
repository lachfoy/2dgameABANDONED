#include "DynamicHealthbar.h"

#include "BaseDamageable.h"

DynamicHealthbar::DynamicHealthbar(int length, int height, BaseDamageable* damageable)
     : Healthbar(0, 0, length, height, damageable)
{}

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