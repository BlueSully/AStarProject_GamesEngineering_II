#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"
#include <thread>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	Game game;
	
	game.Initialize("AStar Threading", 300, 100, 800, 600, SDL_WINDOW_SHOWN);

	while (game.IsRunning())
	{
		game.HandleEvents();
		game.Update(0.0f);
		game.Render();
	}

	game.CleanUp();
	game.UnloadContent();//create GameLoop

	return 0;
}

