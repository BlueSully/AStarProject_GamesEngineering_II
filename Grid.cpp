#include "Grid.h"


Grid::Grid() 
: m_totalNumberWalls(0), 
  m_totalTouchingWalls(0),
  m_topWallCount(1),
  m_bottomWallCount(4)
{

}

void Grid::init(int amount, Size2D gridSize)
{
	int wallindex = 0;
	int wallcount = 0;
	m_gridSize = amount;

	if (m_gridSize == 30)
	{
		m_totalNumberWalls = 3;
		m_totalTouchingWalls = 1;
	}
	else if (m_gridSize == 100)
	{
		m_totalNumberWalls = 6;
		m_totalTouchingWalls = 2;
	}
	else if (m_gridSize == 1000)
	{
		m_totalNumberWalls = 18;
		m_totalTouchingWalls = 4;
	}

	vector<std::pair<string, int>> wallpos;

	for (size_t i = 0; i < m_totalNumberWalls; i++)
	{
		wallindex += static_cast<int>(((m_gridSize / m_totalNumberWalls) - m_totalNumberWalls * 0.5f));
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

	int blockcount = 0;
	for (int row = 0; row < m_gridSize; row++)
	{
		for (int col = 0; col < m_gridSize ; col++)
		{
			// Setup Floor and Walls
			Block blockTile;

			int top = 5;
			int bottom = (m_gridSize - 5);
			
			if(row == wallpos[wallcount].second && wallpos[wallcount].first == "Normal" && col > top && col < bottom)
			{
				blockTile.Init((gridSize.w * row), (gridSize.h * col), gridSize.w, gridSize.h, BlockType::WALL);
			}
			else if ((row == wallpos[wallcount].second && wallpos[wallcount].first == "Bottom") && col > top)
			{
				blockTile.Init((gridSize.w * row), (gridSize.h * col), gridSize.w, gridSize.h, BlockType::WALL);
			}
			else if ((row == wallpos[wallcount].second && wallpos[wallcount].first == "Top") && col < bottom)
			{
				blockTile.Init((gridSize.w * row), (gridSize.h * col), gridSize.w, gridSize.h, BlockType::WALL);
			}		
			else 
			{
				blockTile.Init((gridSize.w * row), (gridSize.h * col), gridSize.w, gridSize.h, BlockType::FLOOR);
				if ((row + col) % 2 == 0)
				{
					blockTile.setColour(Colour(150, 150, 150));
				}
			}
			blockcount++;
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

vector<Block> Grid::getBlockList() const
{
	return m_blockList;
}

int Grid::getGridSize() const
{
	return m_gridSize;
}

Block Grid::getBlockAtPos(Point2D Position) const
{
	for (int i = 0; i < m_gridSize; i++)
	{
		if (Position.x == m_blockList[i].getPosition().x && Position.x == m_blockList[i].getPosition().y)
		{
			return m_blockList[i];
		}
	}
}

Block Grid::getBlockAtIndex(int index) const
{
	if (index < m_blockList.size()) 
	{
		return m_blockList[index];
	}
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
