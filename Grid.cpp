#include "Grid.h"

Grid::Grid()
: m_totalNumberWalls(0),
m_totalTouchingWalls(0),
m_topWallCount(1),
m_bottomWallCount(4),
m_gridInitialised(false)
{

}

//overloaded constructor
Grid::Grid(int amount, Size2D gridSize)
	: m_totalNumberWalls(0),
	m_totalTouchingWalls(0),
	m_topWallCount(1),
	m_bottomWallCount(4),
	m_gridInitialised(false)
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

	for (int i = 0; i < m_totalNumberWalls; i++)
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
		for (int col = 0; col < m_gridSize; col++)
		{
			// Setup Floor and Walls
			NodeBlock blockTile;

			int top = m_gridSize / 5;
			int bottom = (m_gridSize - 5);

			if (!wallpos.empty())//if there are walls
			{
				//start initialising with walls
				if (row == wallpos[wallcount].second && wallpos[wallcount].first == "Normal" && col > top && col < bottom)
				{
					blockTile.Init((gridSize.w * row), (gridSize.h * col), gridSize.w, gridSize.h, BlockType::WALL, blockcount);
				}
				else if ((row == wallpos[wallcount].second && wallpos[wallcount].first == "Bottom") && col > top)
				{
					blockTile.Init((gridSize.w * row), (gridSize.h * col), gridSize.w, gridSize.h, BlockType::WALL, blockcount);
				}
				else if ((row == wallpos[wallcount].second && wallpos[wallcount].first == "Top") && col < bottom)
				{
					blockTile.Init((gridSize.w * row), (gridSize.h * col), gridSize.w, gridSize.h, BlockType::WALL, blockcount);
				}
				else
				{
					blockTile.Init((gridSize.w * row), (gridSize.h * col), gridSize.w, gridSize.h, BlockType::FLOOR, blockcount);
					if ((row + col) % 2 == 0)
					{
						blockTile.setOriginalColour(Colour(150, 150, 150));
					}
				}
			}
			else
			{
				//start initialising without walls
				blockTile.Init((gridSize.w * row), (gridSize.h * col), gridSize.w, gridSize.h, BlockType::FLOOR, blockcount);

				if ((row + col) % 2 == 0)
				{
					blockTile.setOriginalColour(Colour(150, 150, 150));
				}
			}

			blockTile.setNeighbours(m_gridSize, blockcount);
			m_blockList.push_back(blockTile);
			blockcount++;
		}

		if (!wallpos.empty())
		{
			if (row == wallpos[wallcount].second)
			{
				wallcount++;
			}
		}
	}

	wallpos.clear();
	m_gridInitialised = true;
}

//Initilise again function
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

	for (int i = 0; i < m_totalNumberWalls; i++)
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
			NodeBlock blockTile;

			int top = m_gridSize / 5;
			int bottom = (m_gridSize - 5);

			if (!wallpos.empty())
			{
				if (row == wallpos[wallcount].second && wallpos[wallcount].first == "Normal" && col > top && col < bottom)
				{
					blockTile.Init((gridSize.w * row), (gridSize.h * col), gridSize.w, gridSize.h, BlockType::WALL, blockcount);
				}
				else if ((row == wallpos[wallcount].second && wallpos[wallcount].first == "Bottom") && col > top)
				{
					blockTile.Init((gridSize.w * row), (gridSize.h * col), gridSize.w, gridSize.h, BlockType::WALL, blockcount);
				}
				else if ((row == wallpos[wallcount].second && wallpos[wallcount].first == "Top") && col < bottom)
				{
					blockTile.Init((gridSize.w * row), (gridSize.h * col), gridSize.w, gridSize.h, BlockType::WALL, blockcount);
				}
				else
				{
					blockTile.Init((gridSize.w * row), (gridSize.h * col), gridSize.w, gridSize.h, BlockType::FLOOR, blockcount);
					if ((row + col) % 2 == 0)
					{
						blockTile.setOriginalColour(Colour(150, 150, 150));
					}
				}

				blockTile.setNeighbours(m_gridSize, blockcount);
				m_blockList.push_back(blockTile);
				blockcount++;
			}
			else 
			{
				blockTile.Init((gridSize.w * row), (gridSize.h * col), gridSize.w, gridSize.h, BlockType::FLOOR, blockcount);

				if ((row + col) % 2 == 0)
				{
					blockTile.setOriginalColour(Colour(150, 150, 150));
				}

				blockTile.setNeighbours(m_gridSize, blockcount);
				m_blockList.push_back(blockTile);
				blockcount++;
			}
		}
		if (!wallpos.empty()) 
		{
			if (row == wallpos[wallcount].second)
			{
				wallcount++;
			}
		}
	}

	wallpos.clear();
	m_gridInitialised = true;
}

Grid::~Grid()
{
	m_gridInitialised = false;
	m_blockList.clear();
}

void Grid::resetGrid()
{
	for (size_t i = 0; i < m_blockList.size(); i++)
	{
		m_blockList[i].Reset();
	}
}

bool Grid::isGridInitialised() const
{
	return m_gridInitialised;
}

vector<NodeBlock> Grid::getBlockList() const
{
	return m_blockList;
}

int Grid::getGridSize() const
{
	return m_gridSize;
}

NodeBlock Grid::getBlockAtIndex(int index) const
{
	return m_blockList.at(index);
}

void Grid::render(Renderer * render)
{
	for (size_t i = 0; i < m_blockList.size(); i++)
	{
		m_blockList[i].render(render);
	}
}

float Grid::heuristic_cost_estimate(NodeBlock * node, NodeBlock * goal) const
{
	float dX = std::fabsf(node->getPosition().x - goal->getPosition().x);
	float dY = std::fabsf(node->getPosition().y - goal->getPosition().y);
	float heuristic = 1 * (dX + dY);

	return heuristic;
}

float Grid::heuristic_cost_estimate(NodeBlock *node, NodeBlock *goal, NodeBlock *start) const
{
	float heuristic = heuristic_cost_estimate(node, goal);

	//manhattan cost distance with new fix 
	float dx1 = node->getPosition().x - goal->getPosition().x;
	float dy1 = node->getPosition().y - goal->getPosition().y;
	float dx2 = start->getPosition().x - goal->getPosition().x;
	float dy2 = start->getPosition().y - goal->getPosition().y;

	float cross = std::fabsf((dx1 * dy2) - (dx2 * dy1));
	heuristic += (cross * 0.0001f);

	return heuristic;
}

vector<NodeBlock> Grid::aStarAlgorithm(NodeBlock *start, NodeBlock *goal)
{
	std::set<AstarNode *> closedSet;
	std::set<AstarNode *> openSet;

	AstarNode s(start);
	AstarNode g(goal);

	s.gScore = 0;// gScore[start] : = 0

	// For the first node, that value is completely heuristic.
	s.fScore = heuristic_cost_estimate(start, goal); // fScore[start] : = heuristic_cost_estimate(start, goal)

	openSet.insert(&s);

	while (!openSet.empty() && openSet.size() < m_blockList.size())
	{
		AstarNode cur(*openSet.begin());//get Top block
		cur.currentNode->setColour(Colour(0, 255, 255));

		if (cur.currentNode->getIndex() == goal->getIndex())//if current node equals goal
		{
			vector<NodeBlock> path;
			while (cur.prevNode != nullptr)
			{
				cur.prevNode->setColour(Colour(255, 100, 0));
				path.push_back(*cur.prevNode);//add node to path				
				cur = cur.prevNode;
			}
			return path;
		}

		closedSet.insert(&cur);
		openSet.erase(openSet.begin());

		vector<NodeBlock> curNeighbourList;//Get the current neighbours list
		if (cur.currentNode->getTopNeighbour() > -1)//Filling Niehgbour list with valid blocks
		{
			if(m_blockList[cur.currentNode->getTopNeighbour()].getType() != BlockType::WALL)
				curNeighbourList.push_back(m_blockList[cur.currentNode->getTopNeighbour()]);
		}
		if (cur.currentNode->getBottomNeighbour() > -1)
		{
			if (m_blockList[cur.currentNode->getBottomNeighbour()].getType() != BlockType::WALL)
				curNeighbourList.push_back(m_blockList[cur.currentNode->getBottomNeighbour()]);
		}
		if (cur.currentNode->getLeftNeighbour() > -1)
		{
			if (m_blockList[cur.currentNode->getLeftNeighbour()].getType() != BlockType::WALL)
				curNeighbourList.push_back(m_blockList[cur.currentNode->getLeftNeighbour()]);
		}
		if (cur.currentNode->getRightNeighbour() > -1)
		{
			if (m_blockList[cur.currentNode->getRightNeighbour()].getType() != BlockType::WALL)
				curNeighbourList.push_back(m_blockList[cur.currentNode->getRightNeighbour()]);
		}

		for (size_t i = 0; i < curNeighbourList.size(); i++)
		{
			AstarNode * neighbour = new AstarNode(&curNeighbourList[i]);

			if (closedSet.find(neighbour) == closedSet.end())//	if neighbor in closedSet, Ignore
			{
				continue;
			}

			//The distance from start to a neighbor
			//Tentative_gScore : = gScore[current] + dist_between(current, neighbor)
			float dx = cur.currentNode->getPosition().x - neighbour->currentNode->getPosition().x;
			float dy = cur.currentNode->getPosition().y - neighbour->currentNode->getPosition().y;
			float tentative_gScore = cur.gScore + (dx * dy);

			std::set<AstarNode *>::iterator it = openSet.find(neighbour);
			if (it == openSet.end())//if neighbor not in openSet // Discover a new node
			{
				openSet.insert(neighbour);
			}
			else if (tentative_gScore >= neighbour->gScore) // if true This is not a better path. Ignore then
			{
				continue;
			}

			neighbour->gScore = tentative_gScore;
			neighbour->fScore = neighbour->gScore + heuristic_cost_estimate(neighbour->currentNode, goal);
			neighbour->prevNode = cur.currentNode;
			neighbour->currentNode->setColour(Colour(0, 100, 0));
		}
		curNeighbourList.clear();//Clean neighbour looking list
	}

	return vector<NodeBlock>();
}

vector<NodeBlock *> Grid::oldAStarAlgorithm(NodeBlock * start, NodeBlock * goal)
{
	std::map<NodeBlock*, AstarNode> openNodeData;

	auto comparator = [&openNodeData](NodeBlock * n1, NodeBlock * n2)
	{
		bool result = ((openNodeData[n1].fScore) > (openNodeData[n2].fScore));
		return result;
	};

	std::priority_queue<NodeBlock *, vector<NodeBlock*>, decltype(comparator) > openList(comparator);

	openList.push(start);

	// The cost of going from start to start is zero.
	openNodeData[start].gScore = 0;// gScore[start] : = 0

	// For the first node, that value is completely heuristic.
	openNodeData[start].fScore = openNodeData[start].gScore + heuristic_cost_estimate(start, goal); //fScore[start] : = heuristic_cost_estimate(start, goal)

	while (!openList.empty() && openList.size() < m_blockList.size())
	{
		NodeBlock *cur = openList.top();
		
		if ((*cur).getIndex() == goal->getIndex())//if current node equals goal
		{
			vector<NodeBlock *> path;
			while (openNodeData[cur].prevNode != nullptr)
			{
				//openNodeData[cur].prevNode->setColour(Colour(255, 100, 0));
				path.push_back(openNodeData[cur].prevNode);//add node to path				
				cur = openNodeData[cur].prevNode;
			}

			return path;
		}

		openList.pop();// Delete current from openlist as finished with it
		openNodeData[cur].closed = true;
		openNodeData[cur].open = false;

		vector<NodeBlock *> curNeighbourList;//Get the current neighbours list
		if (cur->getTopNeighbour() > -1 && m_blockList[cur->getTopNeighbour()].getType() != BlockType::WALL)//Filling Niehgbour list with valid blocks
		{
			curNeighbourList.push_back(&m_blockList[cur->getTopNeighbour()]);
		}
		if (cur->getBottomNeighbour() > -1 && m_blockList[cur->getBottomNeighbour()].getType() != BlockType::WALL)
		{
			curNeighbourList.push_back(&m_blockList[cur->getBottomNeighbour()]);
		}
		if (cur->getLeftNeighbour() > -1 && m_blockList[cur->getLeftNeighbour()].getType() != BlockType::WALL)
		{
			curNeighbourList.push_back(&m_blockList[cur->getLeftNeighbour()]);
		}
		if (cur->getRightNeighbour() > -1 && m_blockList[cur->getRightNeighbour()].getType() != BlockType::WALL)
		{
			curNeighbourList.push_back(&m_blockList[cur->getRightNeighbour()]);
		}

		//For each neighbor of current
		for (std::vector<NodeBlock*>::iterator iter = curNeighbourList.begin(); iter != curNeighbourList.end(); iter++)
		{
			//If neighbor in closedSet
			if (!openNodeData[*iter].closed)
			{
				//The distance from start to a neighbor
				//Tentative_gScore : = gScore[current] + dist_between(current, neighbor)
				float dx = (cur->getPosition().x - (*iter)->getPosition().x);
				float dy = (cur->getPosition().y - (*iter)->getPosition().y);
				
				float tentative_gScore = openNodeData[cur].gScore + sqrt((dx * dx) + (dy * dy));

				if (!(openNodeData[*iter].open))
				{
					openNodeData[*iter].open = true;
				}
				else if (tentative_gScore > openNodeData[*iter].gScore)//else if tentative_gScore >= gScore[neighbor]
				{
					continue; // This is not a better path.
				}

				//This path is the best until now. Record it!
				openNodeData[*iter].prevNode = cur;//record current node;

				//gScore[neighbor] : = tentative_gScore
				openNodeData[*iter].gScore = tentative_gScore;

				//fScore[neighbor] : = gScore[neighbor] + heuristic_cost_estimate(neighbor, goal)
				openNodeData[*iter].fScore = openNodeData[*iter].gScore + heuristic_cost_estimate((*iter), goal, start);

				if ((openNodeData[*iter].open) && !openNodeData[*iter].closed)
				{				
					openList.push(*iter);
					openNodeData[*iter].closed = true;
					//std::make_heap(const_cast<NodeBlock **>(&openList.top()), const_cast<NodeBlock **>(&openList.top() + openList.size()), comparator);
				}
			}
		}
		curNeighbourList.clear();//Clean neighbour looking list		
	}

	return vector<NodeBlock *>();//Counldn't find path
}

// ASTAR PESUDO-CODE
//function A*(start, goal)
//// The set of nodes already evaluated.
//closedSet : = {}
//	// The set of currently discovered nodes still to be evaluated.
//	// Initially, only the start node is known.
//openSet: = { start }
//	// For each node, which node it can most efficiently be reached from.
//	// If a node can be reached from many nodes, cameFrom will eventually contain the
//	// most efficient previous step.
//cameFrom: = the empty map
//
//	// For each node, the cost of getting from the start node to that node.
//	gScore : = map with default value of Infinity
//	// The cost of going from start to start is zero.
//	gScore[start] : = 0
//	// For each node, the total cost of getting from the start node to the goal
//	// by passing by that node. That value is partly known, partly heuristic.
//	fScore : = map with default value of Infinity
//	// For the first node, that value is completely heuristic.
//	fScore[start] : = heuristic_cost_estimate(start, goal)
//
//	while openSet is not empty
//		current : = the node in openSet having the lowest fScore[] value
//		if current = goal
//			return reconstruct_path(cameFrom, current)
//
//			openSet.Remove(current)
//			closedSet.Add(current)
//			for each neighbor of current
//				if neighbor in closedSet
//					continue		// Ignore the neighbor which is already evaluated.
//									// The distance from start to a neighbor
//					tentative_gScore : = gScore[current] + dist_between(current, neighbor)
//					if neighbor not in openSet	// Discover a new node
//						openSet.Add(neighbor)
//					else if tentative_gScore >= gScore[neighbor]
//						continue		// This is not a better path.
//
//										// This path is the best until now. Record it!
//						cameFrom[neighbor] : = current
//						gScore[neighbor] : = tentative_gScore
//						fScore[neighbor] : = gScore[neighbor] + heuristic_cost_estimate(neighbor, goal)
//
//						return failure
//
//	function reconstruct_path(cameFrom, current)
//		total_path : = [current]
//			while current in cameFrom.Keys :
//				current : = cameFrom[current]
//				total_path.append(current)
//			return total_path