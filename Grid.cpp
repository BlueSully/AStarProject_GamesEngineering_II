#include "Grid.h"


Grid::Grid()
{

}

void Grid::init(int worldsize, Size2D windowResolution)
{
	float sizeX = static_cast<float>(worldsize / arraysize);
	float sizeY = static_cast<float>(worldsize / arraysize) / windowResolution.h;

	for (size_t i = 0; i < arraysize; i++)
	{
		for (size_t j = 0; j < arraysize; j++)
		{
			tester[i][j].Init((sizeX * j), (sizeY * i), sizeX, sizeY, 0);
		}
	}
}

Grid::~Grid()
{
}

void Grid::Update()
{
}

void Grid::render(Renderer * render)
{
	for (size_t i = 0; i < arraysize; i++)
	{
		for (size_t j = 0; j < arraysize; j++)
		{
			tester[i][j].render(render);
		}
	}
}
