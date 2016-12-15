#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"
#include <thread>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	Uint64 LAST = 0;
	float deltaTime = 0;
	Game game;
	
	game.Initialize("AStar Threading", 300, 100, 800, 600, SDL_WINDOW_SHOWN);

	while (game.IsRunning())
	{
		Uint32 NOW = SDL_GetTicks();
		if (NOW > LAST)
		{
			deltaTime = NOW - LAST;
			LAST = NOW;
		}
		game.HandleEvents();
		game.Update(deltaTime);
		game.Render();
	}

	game.CleanUp();
	game.UnloadContent();//create GameLoop

	return 0;
}

