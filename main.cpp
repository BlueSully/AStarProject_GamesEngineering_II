#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"
#include <thread>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	float deltaTime = 0;
	Game game;
	
	game.Initialize("AStar Threading", 300, 100, 800, 600, SDL_WINDOW_SHOWN);

	while (game.IsRunning())
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = static_cast<float>((NOW - LAST) * 1000 / SDL_GetPerformanceFrequency());
		game.HandleEvents();
		game.Update(deltaTime);
		game.Render();
	}

	game.CleanUp();
	game.UnloadContent();//create GameLoop

	return 0;
}

