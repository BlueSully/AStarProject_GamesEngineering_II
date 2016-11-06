#include "Grid.h"


Grid::Grid()
{
	float size = 26.6666667f;
	for (int i = 0; i < 30; i++)
	{
		float x = size * i;
		tester[i].Init((size * i ), 0, size, size, 0);
		
	}
	
}


Grid::~Grid()
{
}

void Grid::Update()
{
}

void Grid::render(SDL_Renderer * render)
{
	for (size_t i = 0; i < 30; i++)
	{
		tester[i].render(render);
	}
}
