#include "Game.h"
#include "TitleState.h"
#include "StageState.h"

int main (int argc, char** argv)
{
    Game &zombieGame = Game::GetInstance();
    Game::GetInstance().Push(new StageState());
    zombieGame.Run();
    return 0;
}
