#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

class Player
{
public:
    Player();

    float posX;
    float posY;

    void handleInput(SDL_Event& e);
    void update(float dt);
    void render(SDL_Renderer* renderer);

private:
    SDL_Rect rect;
    int width;
    int height;
    int velX;
    int velY;
    float moveSpeed;
};

Player::Player()
{
    // initialize everything
    posX = 100.0f;
    posY = 100.0f;
    rect.x = (int)posX;
    rect.y = (int)posY;
    rect.w = 40;
    rect.h = 64;
    velX = 0;
    velY = 0;
    moveSpeed = 200.0f;
}

void Player::handleInput(SDL_Event& e) // use keystate instead?
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        const SDL_Keycode keyCode = e.key.keysym.sym;
        if (keyCode == SDLK_UP)
            velY = -1;
        if (keyCode == SDLK_DOWN)
            velY = 1;
        if (keyCode == SDLK_LEFT)
            velX = -1;
        if (keyCode == SDLK_RIGHT)
            velX = 1;
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        const SDL_Keycode keyCode = e.key.keysym.sym;
        if (e.key.keysym.sym == SDLK_UP)
            velY = 0;
        if (e.key.keysym.sym == SDLK_DOWN)
            velY = 0;
        if (e.key.keysym.sym == SDLK_LEFT)
            velX = 0;
        if (e.key.keysym.sym == SDLK_RIGHT)
            velX = 0;
    }
}

void Player::update(float dt)
{
    // update the internal position
    posX += velX * moveSpeed * dt;
    posY += velY * moveSpeed * dt;

    // also reposition the visual representation of the player
    rect.x = (int)posX - (rect.w / 2);
    rect.y = (int)posY - (rect.h);
}

void Player::render(SDL_Renderer* renderer)
{
    // draw the player rect representing the player
    SDL_SetRenderDrawColor(renderer, 0x29, 0x65, 0xff, 0xff); // #2965ff blue
    SDL_RenderFillRect(renderer, &rect);

    // draw the origin position representing the actual x and y positions
    SDL_SetRenderDrawColor(renderer, 0xeb, 0xd5, 0x17, 0xff); // #ebd517 yellow
    SDL_RenderFillRect(renderer, new SDL_Rect({ (int)posX - 3, (int)posY - 3, 6, 6 }));
}

#endif