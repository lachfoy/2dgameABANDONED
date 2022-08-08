#ifndef PLAYERDEBUGTEXT_H
#define PLAYERDEBUGTEXT_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "TextObject.h"

#include "Player.h"

class PlayerDebugText : public TextObject
{
public:
    inline PlayerDebugText(int x, int y, std::string string, TTF_Font* font, Player* player);

    inline void updateString(std::string string); // these should be added as a derived class
    inline void updatePosition(const int& newX, const int& newY); // these should be added as a derived class

    inline void update(float dt) override; // these should be added as a derived class

private:

    // does NOT own
    Player* player;

};

PlayerDebugText::PlayerDebugText(int x, int y, std::string string, TTF_Font* font, Player* player)
     : TextObject(x, y, string, font)
{
    this->player = player;
}

void PlayerDebugText::update(float dt)
{
    string = "Fireball Charges: " + std::to_string(player->getAmmo()) + "/3";
}

#endif