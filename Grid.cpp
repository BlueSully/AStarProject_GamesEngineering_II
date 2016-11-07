#include "Grid.h"


Grid::Grid()
{

}

void Grid::init(Vector2 WinSize)
{
	float sizex = static_cast<float>(WinSize.x / arrayX) * 2;
	float sizey = static_cast<float>(WinSize.y / arrayY) * 1.999f;

	for (size_t i = 0; i < arrayX; i++)
	{
		for (size_t j = 0; j < arrayY; j++)
		{
			if (j % 3 == 0) 
			{
				//sizex = (static_cast<float>((WinSize.x / arrayX)-1) * 2) ;
				tester[i][j].Init((sizex * j) - 0.75f, (sizey * i), sizex, sizey, 0);
			}
			else 
			{
				tester[i][j].Init((sizex * j), (sizey * i), sizex, sizey, 0);
			}
		}
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
	for (size_t i = 0; i < arrayX; i++)
	{
		for (size_t j = 0; j < arrayY; j++)
		{
			tester[i][j].render(render);
		}
	}
}
