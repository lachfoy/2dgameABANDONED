#include "Game.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

int main(int argc, char* argv[])
{
    Game game = Game();
    if(game.init(SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        game.run();
    }

    return 0;
}