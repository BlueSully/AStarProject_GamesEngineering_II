#pragma once
//Job To hold all the blocks and to find and add blocks to the level
#include "SDL.h"
#include "Block.h"
class Grid
{
private:
	static const int arrayX = 30;
	static const int arrayY = 30;
	Block tester[arrayX][arrayY];

public:
	Grid();
	void init(Vector2 WinSize);
	~Grid();

	void Update();
	void render(SDL_Renderer* render);
};

