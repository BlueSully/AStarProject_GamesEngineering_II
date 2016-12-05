#pragma once
//Job To hold all the blocks and to find and add blocks to the level
#include "SDL.h"
#include "NodeBlock.h"
#include "Enemy.h"
#include "BasicTypes.h"

class Grid
{
private:
	vector<NodeBlock> m_blockList;
	int m_gridSize;
	int m_totalNumberWalls;
	int m_totalTouchingWalls;
	int m_topWallCount;
	int m_bottomWallCount;

public:
	Grid();
	void init(int worldsize, Size2D windowResolution);
	~Grid();

	vector<NodeBlock> getBlockList() const;
	int getGridSize() const;
	NodeBlock getBlockAtPos(Point2D Position) const;
	NodeBlock getBlockAtIndex(int index) const;

	void Update();
	void render(Renderer* render);

	void aStarAlgorithm(NodeBlock * start, NodeBlock * goal, Enemy * entity);
};

