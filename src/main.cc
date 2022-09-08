#include "game.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

int main(int argc, char* argv[])
{
    Game* game = new Game();
    
    if(game->Init(SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        game->Run();
    }

    delete game;

    return 0;
}