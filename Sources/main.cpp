#include "Game.h"

void kore(int argc, char **argv)
{
    // make sure there are some valid command line arguments
    static char *argvn[] = { (char*)"KoolboxGame" };
    if (!argv)
    {
        argc = 1;
        argv = argvn;
    }

	// create game
    auto *game = new Game::Game(argc, argv);
    Kore::System::start();
}
