#include "DynamicHealthbar.h"

#include "base_actor.h"

DynamicHealthbar::DynamicHealthbar(int length, int height, BaseActor* damageable)
     : Healthbar(0, 0, length, height, damageable)
{
    
}

void DynamicHealthbar::updatePosition()
{
    int newX = (int)damageable->pos().x;
    int newY = (int)damageable->pos().y - damageable->height() - height - 2; // newY - objH - healthbarH - some padding value

    this->x = newX - (int)(length / 2.0f);
    this->y = newY - (int)(height / 2.0f);

    bg_rect.x = this->x;
    bg_rect.y = this->y;

    health_rect.x = this->x;
    health_rect.y = this->y;
}