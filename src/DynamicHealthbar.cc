#include "DynamicHealthbar.h"

// #include "base_character.h"

// DynamicHealthbar::DynamicHealthbar(int length, int height, BaseCharacter* mCharacter)
//      : HealthBar(0, 0, length, height, mCharacter)
// {
    
// }

// void DynamicHealthbar::UpdatePosition()
// {
//     int newX = (int)mCharacter->pos().x;
//     int newY = (int)mCharacter->pos().y - mCharacter->height() - mHeight - 2; // newY - objH - healthbarH - some padding value

//     this->x = newX - (int)(mLength / 2.0f);
//     this->y = newY - (int)(mHeight / 2.0f);

//     mBgRect.x = this->x;
//     mBgRect.y = this->y;

//     mResourceRect.x = this->x;
//     mResourceRect.y = this->y;
// }