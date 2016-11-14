#include "Block.h"

Block::Block()
{

}

Block::~Block()
{

}

void Block::Init(float posX, float posY, float width, float height, BlockType type)
{
	m_rectangle.pos.x = posX;
	m_rectangle.pos.y = posY;
	m_rectangle.size.w = width;
	m_rectangle.size.h = height;
	m_type = type;
	initializeColour();
}

void Block::initializeColour()
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

void Block::Update()
{

}

void Block::render(Renderer * r)
{
	r->drawWorldFillRect(m_rectangle, m_colour);
}

Point2D Block::getPosition() const
{
	return Point2D(m_rectangle.pos.x, m_rectangle.pos.y);
}

Size2D Block::getSize() const
{
	return Size2D(m_rectangle.size.w, m_rectangle.size.h);
}

BlockType Block::getType() const
{
	return m_type;
}

void Block::setType(BlockType val)
{
	m_type = val;
}

void Block::setColour(Colour val)
{
	m_colour = val;
}