#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"
#include <thread>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
	Game* game = new Game();

	//Adjust screen positions as needed
	game->Initialize("AStar Threading",300,100,800,600, SDL_WINDOW_SHOWN);
	DEBUG_MSG("Game Init Successful");

	while(game->IsRunning())
	{
		game->HandleEvents();
		game->Update();
		game->Render();
	}

	game->CleanUp();
	game->UnloadContent();
	
	return 0;
}

