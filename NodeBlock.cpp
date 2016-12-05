#include "NodeBlock.h"

NodeBlock::NodeBlock()
{

}

NodeBlock::~NodeBlock()
{

}

void NodeBlock::Init(float posX, float posY, float width, float height, BlockType type)
{
	m_rectangle.pos.x = posX;
	m_rectangle.pos.y = posY;
	m_rectangle.size.w = width;
	m_rectangle.size.h = height;
	m_type = type;
	initializeColour();

}

void NodeBlock::initializeColour()
{
	switch (m_type)
	{
	case BlockType::WALL:
		m_colour = { 0, 0, 0, 255 };
		break;
	case BlockType::FLOOR:
		m_colour = { 200, 200, 200, 255 };
		break;
	}
}

void NodeBlock::Update()
{

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

void NodeBlock::setType(BlockType val)
{
	m_type = val;
}

void NodeBlock::setColour(Colour val)
{
	m_colour = val;
}

void NodeBlock::setNeighbours(int gridSize, int currentIndex)
{
	m_currentIndex = currentIndex;
	if (m_currentIndex - 1 > 0)
	{
		m_topBlockIndex = m_currentIndex - 1;
	}
	if (m_currentIndex + 1 < gridSize)
	{
		m_bottomBlockIndex = m_currentIndex + 1;
	}
	if (m_currentIndex + gridSize < (gridSize * gridSize))
	{
		m_rightBlockIndex = m_currentIndex + gridSize;
	}
	if (m_currentIndex - gridSize > 0)
	{
		m_leftBlockIndex = m_currentIndex - gridSize;
	}
}