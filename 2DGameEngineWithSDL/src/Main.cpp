#define SDL_MAIN_HANDLED

#include "Game.h"

int main()
{
	Game* game = new Game();
	game->Initialize(800, 600);

	while (game->IsRunning())
	{
		game->PorcessInput();
		game->Update();
		game->Render();
	}

	delete(game);
}