#include "Grid.h"


Grid::Grid() 
: m_totalNumberWalls(0), 
  m_totalTouchingWalls(0),
  m_topWallCount(1),
  m_bottomWallCount(4)
{

}

void Grid::init(int amount, Size2D windowResolution)
{
	float sizeX = windowResolution.w / amount;
	float sizeY = windowResolution.h / amount;

	int wallindex = 0;
	int wallcount = 0;

	if (amount == 10)
	{
		m_totalNumberWalls = 2;
	}
	else if (amount == 30)
	{
		m_totalNumberWalls = 3;
		m_totalTouchingWalls = 1;
	}
	else if (amount == 100)
	{
		m_totalNumberWalls = 6;
		m_totalTouchingWalls = 2;
	}
	else if (amount == 1000)
	{
		m_totalNumberWalls = 18;
		m_totalTouchingWalls = 4;
	}

	vector<std::pair<string, int>> wallpos;

	int count = 0;

	for (size_t i = 0; i < m_totalNumberWalls; i++)
	{
		wallindex += ((amount / m_totalNumberWalls) - m_totalNumberWalls * 0.5f);
		if (i == m_topWallCount)
		{
			wallpos.push_back(make_pair("Top", wallindex));
			m_topWallCount += 6;
		}
		else if (i == m_bottomWallCount)
		{
			wallpos.push_back(make_pair("Bottom", wallindex));
			m_bottomWallCount += 6;
		}
		else
		{
			wallpos.push_back(make_pair("Normal", wallindex));
		}
	}

	int lastrow = 0;
	for (int row = 0; row < amount; row++)
	{
		for (int col = 0; col < amount; col++)
		{
			// Setup Floor and Walls
			Block blockTile;

			int top = 5;
			int bottom = (amount - 5);
			
			if(row == wallpos[wallcount].second && wallpos[wallcount].first == "Normal" && col > top && col < bottom)
			{
				blockTile.Init((sizeX * row), (sizeY * col), sizeX, sizeY, BlockType::WALL);
			}
			else if ((row == wallpos[wallcount].second && wallpos[wallcount].first == "Bottom") && col > top)
			{
				blockTile.Init((sizeX * row), (sizeY * col), sizeX, sizeY, BlockType::WALL);
			}
			else if ((row == wallpos[wallcount].second && wallpos[wallcount].first == "Top") && col < bottom)
			{
				blockTile.Init((sizeX * row), (sizeY * col), sizeX, sizeY, BlockType::WALL);
			}		
			else 
			{
				blockTile.Init((sizeX * row), (sizeY * col), sizeX, sizeY, BlockType::FLOOR);
				if ((row + col) % 2 == 0)
				{
					blockTile.setColour(Colour(100, 100, 100));
				}
			}

			m_blockList.push_back(blockTile);
		}

		if (row == wallpos[wallcount].second) 
		{
			wallcount++;
		}
	}

	wallpos.clear();
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
