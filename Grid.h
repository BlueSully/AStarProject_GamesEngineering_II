#pragma once
//Job To hold all the blocks and to find and add blocks to the level
#include "SDL.h"
#include "Block.h"
class Grid
{
private:
	Block tester[30];
// an 2d array each element will hold an array of a certain size and fill them in
	// array[0] = {1,2,3,4,5,6,7,8,9,10};
public:
	Grid();
	~Grid();

	void Update();
	void render(SDL_Renderer* render);
};

