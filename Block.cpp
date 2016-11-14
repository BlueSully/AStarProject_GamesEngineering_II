#include "Block.h"

Block::Block()
{

}

void Block::Update()
{
}

void Block::Init(float posX, float posY, float width, float height, int type)
{
	m_rectangle.pos.x = posX;
	m_rectangle.pos.y = posY;
	m_rectangle.size.w = width;
	m_rectangle.size.h = height;
	m_type = static_cast<BlockType>(type);
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
		m_colour = { 255, 255, 0, 255 };
		break;
	}
}

Point2D Block::getPosition() const
{
	return Point2D(m_rectangle.pos.x, m_rectangle.pos.y);
}

Size2D Block::getSize() const
{
	return Size2D(m_rectangle.size.w, m_rectangle.size.h);
}

bool Block::isBlockWall() const
{
	return m_isWall;
}

void Block::render(Renderer * r)
{
	r->drawWorldFillRect(m_rectangle, m_colour);
	r->drawWorldRect(m_rectangle, Colour(0, 255, 0));
}

Block::~Block()
{

}
