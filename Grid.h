#pragma once
//Job To hold all the blocks and to find and add blocks to the level
#include "SDL.h"
#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include "NodeBlock.h"
#include "Enemy.h"
#include "BasicTypes.h"

//struct AstarNode
//{
//	NodeBlock * currentNode;
//	NodeBlock * prevNode;
//	float fScore;
//	float gScore;
//	bool open;
//	bool closed;
//
//	AstarNode() : currentNode(nullptr),
//		prevNode(nullptr),
//		fScore(std::numeric_limits<float>::infinity()),
//		gScore(std::numeric_limits<float>::infinity()),
//		open(false),
//		closed(false)
//	{
//
//	}
//
//	AstarNode(NodeBlock *n) : currentNode(n),
//		prevNode(nullptr),
//		fScore(std::numeric_limits<float>::infinity()), 
//		gScore(std::numeric_limits<float>::infinity()),
//		open(false),
//		closed(false)
//	{
//
//	}
//};
//
//struct comparator 
//{
//	bool operator() (const AstarNode &lhs, const AstarNode &rhs) const
//	{
//		return lhs.fScore < rhs.fScore;
//	}
//};

class Grid
{
private:
	vector<NodeBlock> m_blockList;
	int m_gridSize;
	int m_totalNumberWalls;
	int m_totalTouchingWalls;
	int m_topWallCount;
	int m_bottomWallCount;
	bool m_gridInitialised;
public:
	Grid();
	Grid(int amount, Size2D gridSize);
	void init(int amount, Size2D gridSize);
	~Grid();

	void resetGrid();

	bool isGridInitialised() const;
	vector<NodeBlock> getBlockList() const;
	int getGridSize() const;
	NodeBlock getBlockAtIndex(int index) const;

	void render(Renderer* render);
	float heuristic_cost_estimate(NodeBlock *node, NodeBlock *goal) const;
	float heuristic_cost_estimate(NodeBlock *node, NodeBlock *goal, NodeBlock *start) const;

	vector<NodeBlock> oldAStarAlgorithm(NodeBlock * start, NodeBlock * goal);
	vector<NodeBlock> aStarAlgorithm(NodeBlock * start, NodeBlock * goal);
};

