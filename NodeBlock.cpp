#include "NodeBlock.h"

NodeBlock::NodeBlock()
{

}

NodeBlock::~NodeBlock()
{

}

void NodeBlock::Init(float posX, float posY, float width, float height, BlockType type, int index)
{
	m_rectangle.pos.x = posX;
	m_rectangle.pos.y = posY;
	m_rectangle.size.w = width;
	m_rectangle.size.h = height;
	m_type = type;
	m_currentIndex = index;
	initializeColour();
	m_colour = m_originalColour;
	m_isEnemyOccupying = false;
}

void NodeBlock::initializeColour()
{
	switch (m_type)
	{
	case BlockType::WALL:
		m_originalColour = { 0, 0, 0, 255 };
		break;
	case BlockType::FLOOR:
		m_originalColour = { 200, 200, 200, 255 };
		break;
	}
}

void NodeBlock::render(Renderer * r)
{
	r->drawWorldFillRect(m_rectangle, m_colour);
}

Point2D NodeBlock::getPosition() const
{
	return Point2D(m_rectangle.pos.x, m_rectangle.pos.y);
}

Size2D NodeBlock::getSize() const
{
	return Size2D(m_rectangle.size.w, m_rectangle.size.h);
}

BlockType NodeBlock::getType() const
{
	return m_type;
}

void NodeBlock::Reset()
{
	m_colour = m_originalColour;
}

void NodeBlock::setOriginalColour(Colour val)
{
	m_originalColour = val;
	m_colour = m_originalColour;
}

void NodeBlock::setType(BlockType val)
{
	m_type = val;
}

int NodeBlock::getIndex() const
{
	return m_currentIndex;
}

void NodeBlock::setSolidColour(Colour val)
{
	m_colour = val;
}

void NodeBlock::setColour(Colour val)
{
	m_colour.r = val.r;
	m_colour.g = val.g;
	m_colour.b = val.b;
}

void NodeBlock::setMarked(bool value)
{
	if (value) 
	{
		m_colour.r = 100;
		m_colour.g = 100; 
	}
}

bool NodeBlock::getIsEnemyOccupying() const
{
	return m_isEnemyOccupying;
}

void NodeBlock::setIsEnemyOccupying(bool value)
{
	m_isEnemyOccupying = value;
}

void NodeBlock::setNeighbours(int gridSize, int currentIndex)
{
	if ((m_currentIndex - 1) % gridSize != gridSize - 1 && m_currentIndex - 1 > -1)
	{
		m_topBlockIndex = m_currentIndex - 1;
	}
	else
	{
		m_topBlockIndex = std::numeric_limits<int>::min();
	}

	if ((m_currentIndex + 1) % gridSize != 0)
	{
		m_bottomBlockIndex = m_currentIndex + 1;
	}
	else
	{
		m_bottomBlockIndex = std::numeric_limits<int>::min();
	}

	if (m_currentIndex + gridSize < (gridSize * gridSize))
	{
		m_rightBlockIndex = m_currentIndex + gridSize;
	}
	else
	{
		m_rightBlockIndex = std::numeric_limits<int>::min();
	}

	if (m_currentIndex - gridSize > -1)
	{
		m_leftBlockIndex = m_currentIndex - gridSize;
	}
	else 
	{
		m_leftBlockIndex = std::numeric_limits<int>::min();
	}
}

int NodeBlock::getTopNeighbour() const
{
	return m_topBlockIndex;
}

int NodeBlock::getBottomNeighbour() const
{
	return m_bottomBlockIndex;
}

int NodeBlock::getLeftNeighbour() const
{
	return m_leftBlockIndex;
}

int NodeBlock::getRightNeighbour() const
{
	 return m_rightBlockIndex;
}