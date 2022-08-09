#ifndef PLAYERDEBUGTEXT_H
#define PLAYERDEBUGTEXT_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "BaseTextObject.h"

#include "Player.h"

class PlayerDebugText : public BaseTextObject
{
public:
    inline PlayerDebugText(int x, int y, std::string text, TTF_Font* font, Player* player);

    inline void updateText(std::string text); // these should be added as a derived class
    inline void updatePosition(const int& newX, const int& newY); // these should be added as a derived class

    inline void update(float dt) override; // these should be added as a derived class

private:

    // does NOT own
    Player* player;

};

PlayerDebugText::PlayerDebugText(int x, int y, std::string text, TTF_Font* font, Player* player)
     : BaseTextObject(x, y, text, font)
{
    this->player = player;
}

void PlayerDebugText::update(float dt)
{
    text = "Fireball Charges: " + std::to_string(player->getAmmo()) + "/3";
}

#endif