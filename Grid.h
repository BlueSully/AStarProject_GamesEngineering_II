#pragma once
//Job To hold all the blocks and to find and add blocks to the level
#include "SDL.h"
#include "Block.h"
#include "BasicTypes.h"

class Grid
{
private:
	vector<Block> m_blockList;
	int m_gridSize;
	int m_totalNumberWalls;
	int m_totalTouchingWalls;
	int m_topWallCount;
	int m_bottomWallCount;

public:
	Grid();
	void init(int worldsize, Size2D windowResolution);
	~Grid();

	vector<Block> getBlockList() const;
	Block getBlockAtPos(Point2D Position) const;
	Block getBlockAtIndex(int index) const;
	void Update();
	void render(Renderer* render);
};

