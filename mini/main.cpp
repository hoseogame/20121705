#include <iostream>
#include "GameManager.h"


int main()
{
	GameManager* game = new GameManager();
	Screen::Instance()->ScreenInit();

	while( !game->Exit() )
	{
		game->Update();
		game->Render();
	}

	delete game;
	Screen::Instance()->ScreenRelease();

	return 0;
}