#include "Block.h"

Block::Block()
{

}

void Block::Update()
{
}

void Block::Init(float posX, float posY, float width, float height, int type)
{
	m_rectangle.x = static_cast<int>(posX);
	m_rectangle.y = static_cast<int>(posY);
	m_rectangle.w = static_cast<int>(width);
	m_rectangle.h = static_cast<int>(height);
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

Vector2 Block::getPosition() const
{
	return Vector2(m_rectangle.x, m_rectangle.y);
}

Vector2 Block::getSize() const
{
	return Vector2(m_rectangle.w, m_rectangle.h);
}

bool Block::isBlockWall() const
{
	return m_isWall;
}

void Block::render(SDL_Renderer * render)
{
	SDL_SetRenderDrawColor(render, m_colour.r, m_colour.g, m_colour.b, m_colour.a);
	SDL_RenderFillRect(render, &m_rectangle);

}

Block::~Block()
{

}
