#include "Grid.h"


Grid::Grid() : m_numberWalls(0)
{

}

void Grid::init(int amount, Size2D windowResolution)
{
	float sizeX = windowResolution.w / amount;
	float sizeY = windowResolution.h / amount;

	if (amount == 30)
	{
		m_numberWalls = 3;
	}
	else if (amount == 100)
	{
		m_numberWalls = 6;
	}
	else if (amount == 1000)
	{
		m_numberWalls = 18;
	}
	
	for (int row = 0; row < amount; row++)
	{
		for (int col = 0; col < amount; col++)
		{
			// Setup Floor
			Block temp;
			if (col >= 3 && col < amount - 3 && row == (amount / m_numberWalls))
			{
				temp.Init((sizeX * row), (sizeY * col), sizeX, sizeY, BlockType::WALL);
			}
			else
			{
				temp.Init((sizeX * row), (sizeY * col), sizeX, sizeY, BlockType::FLOOR);
				if ((row + col) % 2 == 0)
				{
					temp.setColour(Colour(100, 100, 100));
				}
			}
			m_blockList.push_back(temp);
		}
	}

	//Debug Code
	int size = 8;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if ((i >= size / 4 && i < size - 2 && j % i size / 3 == 1))
			{
				cout << "6 ";
			}
			else if ((i + j) % 2 == 0)
			{
				cout << "1 ";
			}
			else
			{
				cout << "0 ";
			}
		}
		cout << '\n';
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
	for (size_t i = 0; i < m_blockList.size(); i++)
	{
		m_blockList[i].render(render);
	}
}
